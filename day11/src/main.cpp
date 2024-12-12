#include "util/util.h"

#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cstdlib>
#include <span>
#include <vector>
#include <unordered_map>

namespace aoc2024::day11
{
using util::countDigits;
using util::isEven;

std::uint64_t evolvePebbles(std::span<std::uint64_t> input, std::uint64_t times)
{
    using namespace ::ranges;
    using PebbleGeneration = std::unordered_map<std::uint64_t, std::uint64_t>;
    auto currentGeneration = [&]
    {
        PebbleGeneration result;
        for (auto pebble : input)
            ++result[pebble];
        return result;
    }();

    for (std::size_t i = 0; i < times; ++i)
    {
        PebbleGeneration nextGeneration;
        for (const auto& [number, count] : currentGeneration)
        {
            if (number == 0)
                nextGeneration[1] += count;
            else if (auto digits = countDigits(number); isEven(digits))
            {
                auto [div, mod] =
                    std::ldiv(number, std::uint64_t(std::pow(10, digits / 2)));
                nextGeneration[div] += count;
                nextGeneration[mod] += count;
            }
            else
                nextGeneration[number * 2024] += count;
        }
        currentGeneration = std::move(nextGeneration);
    }
    return accumulate(currentGeneration,
                      std::uint64_t{0},
                      std::plus{},
                      &PebbleGeneration::value_type::second);
}

/**
 * A slightly optimized version of evolvePebbles.
 * Has an overhead doing grouping and sorting, but saves on memory allocations
 * and has functions.
 * Probably the most performant solution would be with flat_map.
 * @param input
 * @param times
 * @return
 */
std::uint64_t evolvePebbles1(std::span<std::uint64_t> input, std::uint64_t times)
{
    using namespace ::ranges;
    using PebleCounter = std::pair<std::uint64_t, std::uint64_t>;
    using Pebles = std::vector<PebleCounter>;

    auto currentGeneration = input
                             | views::transform(
                                 [](auto val)
                                 {
                                     return PebleCounter{val, 1};
                                 })
                             | to<Pebles>();
    std::vector<PebleCounter> nextGeneration;

    for (std::size_t i = 0; i < times; ++i)
    {
        nextGeneration.clear();
        nextGeneration.reserve(std::size(currentGeneration) * 2);

        for (const auto& [number, count] : currentGeneration)
        {
            if (number == 0)
                nextGeneration.emplace_back(1, count);
            else if (auto digits = countDigits(number); isEven(digits))
            {
                auto [div, mod] =
                    std::ldiv(number, std::uint64_t(std::pow(10, digits / 2)));
                nextGeneration.emplace_back(div, count);
                nextGeneration.emplace_back(mod, count);
            }
            else
                nextGeneration.emplace_back(number * 2024, count);
        }

        nextGeneration |= actions::sort;
        currentGeneration.clear();
        currentGeneration.reserve(std::size(nextGeneration));
        currentGeneration |= actions::push_back(
            nextGeneration
            | views::chunk_by(
                [](const auto& a, const auto& b)
                {
                    return a.first == b.first;
                })
            | views::transform(
                [](auto group)
                {
                    return accumulate(group,
                                      PebleCounter{0, 0},
                                      [](auto acc, const auto& val)
                                      {
                                          return PebleCounter{val.first,
                                                              acc.second + val.second};
                                      });
                }));
    }
    return accumulate(currentGeneration, std::uint64_t{0}, std::plus{}, &PebleCounter::second);
}

namespace part1
{


void test()
{
    {
        std::vector<std::uint64_t> input = {125, 17};
        auto solution = evolvePebbles(input, 25);
        fmt::print("Part I Test1: {}\n", solution);
    }
}

void solve()
{
    std::vector<std::uint64_t> input{64554, 35, 906, 6, 6960985, 5755, 975820, 0};
    auto solution = evolvePebbles(input, 25);
    fmt::print("Part I Solution: {}\n", solution);  // 175006
}
}  // namespace part1
namespace part2
{
void solve()
{
    std::vector<std::uint64_t> input{64554, 35, 906, 6, 6960985, 5755, 975820, 0};
    auto solution = evolvePebbles(input, 75);
    fmt::print("Part II Solution1: {}\n", solution);  // 207961583799296 - 11-15ms
}
void solve2()
{
    std::vector<std::uint64_t> input{64554, 35, 906, 6, 6960985, 5755, 975820, 0};
    auto solution = evolvePebbles1(input, 75);
    fmt::print("Part II Solution2: {}\n", solution);  // 207961583799296 - 9-11ms
}
}  // namespace part2
}  // namespace aoc2024::day11

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day11;
    part1::test();
    util::withTimer("part1::solve", part1::solve);
    util::withTimer("part2::solve", part2::solve);
    util::withTimer("part2::solve2", part2::solve2);
    return 0;
}