#include "util/util.h"
#include "util/functional.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/dynamic_bitset.hpp>

#include <ctre.hpp>

#include <fstream>
#include <string>
#include <string_view>

namespace aoc2024::day23
{
struct LanParty
{
    using Computer = std::string;
    using To = boost::unordered_flat_set<Computer>;
    using Connections = boost::unordered_flat_map<Computer, To>;

    Connections connections;
    std::vector<std::pair<std::string, std::string>> flatConnections;
};

LanParty loadInputs(const std::string& filename)
{
    std::ifstream file(filename);
    // process line-by-line
    LanParty lanParty;
    for (std::string line; std::getline(file, line);)
    {
        auto [whole, from, to] = ctre::match<R"(([a-z][a-z])-([a-z][a-z]))">(line);
        lanParty.connections[from.to_string()].insert(to.to_string());
        lanParty.connections[to.to_string()].insert(from.to_string());
        lanParty.flatConnections.emplace_back(from.to_string(), to.to_string());
        lanParty.flatConnections.emplace_back(to.to_string(), from.to_string());
    }
    return lanParty;
}

namespace part1
{
std::size_t solve(const LanParty& lanParty)
{
    // ugly, let's not waste time, since Part II may be brutal
    using namespace ::ranges;
    boost::unordered_flat_set<std::tuple<std::string, std::string, std::string>> sets;
    for (const auto& [from, to] : lanParty.connections
                                      | views::filter(
                                          [](const auto& fromTo)
                                          {
                                              return fromTo.first[0] == 't';
                                          }))
    {
        auto threesomes =
            views::cartesian_product(to, to)
            | views::filter(
                [&](const auto& fromTo)
                {
                    const auto& [from2, to2] = fromTo;
                    return from2 > to2
                           && lanParty.connections.at(from2).contains(to2);
                });
        for (auto threesome : threesomes)
        {
            auto [from2, to2] = threesome;
            std::array three{from, from2, to2};
            std::sort(std::begin(three), std::end(three));
            sets.emplace(three[0], three[1], three[2]);
        }
    }
    return std::size(sets);
}
}  // namespace part1

namespace part2
{
// brute force
std::string solve(const LanParty& party)
{
    using namespace ::ranges;
    /**
     * since them maximum number of connections is 13. Checking all possible groups
     * for every given vertex is 2**13 (8192) which is not that much event when
     * multiplied by large number of vertices.
     * Ignoring bad options - also helps to speed up the process.
     */
    std::size_t max = 3;  // 3 is chosen arbitrary, I doubt that the solution is below 5
    std::vector<std::string> largestGroup;
    for (const auto& [vertex, connections] : party.connections)
    {
        for (std::uint16_t num = 0; num <= (1 << std::size(connections)); ++num)
        {
            boost::dynamic_bitset<> bits{std::size(connections), num};
            if (bits.count() < max)
                continue;

            auto selectedComputers =
                connections | views::enumerate
                | views::filter(
                    [&](const auto& c)
                    {
                        return bits[c.first];
                    })
                | views::transform(util::functional::selectIth<1>) | to_vector;

            const auto formGroup = all_of(  //
                views::cartesian_product(selectedComputers, selectedComputers),
                [&](const auto& fromTo)
                {
                    const auto& [from, to] = fromTo;
                    return from == to || party.connections.at(from).contains(to);
                });
            if (formGroup)
            {
                selectedComputers.push_back(vertex);
                largestGroup = std::move(selectedComputers);
                max = std::size(largestGroup);
            }
        }
    }
    return fmt::format("{}", fmt::join(actions::sort(largestGroup), ","));
}
}  // namespace part2
}  // namespace aoc2024::day23

int main(int argc, char** argv)
{
    using namespace aoc2024::day23;
    std::span<char*> args(argv, argc);
    if (args.size() > 1)
    {
        auto inputs = loadInputs(args[1]);
        fmt::print("Part I: {}\n", part1::solve(inputs));
        auto part2Solution =
            aoc2024::util::withTimer("Part2", std::bind_front(part2::solve, inputs));
        fmt::print("Part II: {}\n", part2Solution); // 75ms
    }

    return 0;
}