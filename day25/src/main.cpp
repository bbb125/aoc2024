#include "util/util.h"
#include "util/functional.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <vector>
#include <string>
#include <fstream>

namespace aoc2024::day25
{
struct Inputs
{
    using Heights = std::vector<int>;
    int height = 0;
    std::vector<Heights> locks;
    std::vector<Heights> keys;
};

Inputs loadFromFile(const std::string& filename)
{
    using namespace ::ranges;

    Inputs result;

    std::ifstream file(filename);
    std::optional<bool> isLock;
    Inputs::Heights current;
    int height = 0;
    for (std::string line; std::getline(file, line);)
    {
        if (std::empty(line))
        {
            if (result.height == 0)
                result.height = height;
            (*isLock ? result.locks : result.keys).push_back(std::move(current));
            current.clear();
            isLock = std::nullopt;
        }
        else
        {
            ++height;
            if (std::empty(current))
                current.resize(std::size(line), 0);

            std::size_t total = 0;
            for (auto num : line | views::enumerate
                                | views::filter(
                                    [](const auto& pair)
                                    {
                                        return pair.second == '#';
                                    })
                                | views::transform(util::functional::selectIth<0>))
            {
                current[num] += 1;
                total += 1;
            }
            if (!isLock.has_value())
                isLock = (total == std::size(line));
        }
    }
    (*isLock ? result.locks : result.keys).push_back(std::move(current));
    return result;
}

namespace part1
{
int countMatchingPairs(const Inputs& inputs)
{
    using namespace ::ranges;
    int total = 0;
    for (const auto& [lock, key] : views::cartesian_product(inputs.locks, inputs.keys))
    {
        total += all_of(views::zip(lock, key),
                        [height = inputs.height](const auto& pair)
                        {
                            return pair.first + pair.second <= height;
                        });
    }
    return total;
}
}  // namespace part1
}  // namespace aoc2024::day25

int main(int argc, char* argv[])
{
    using namespace aoc2024::day25;
    if (auto args = std::span(argv, argc); std::size(args) > 1da)
    {
        auto inputs = loadFromFile(args[1]);
        fmt::print("keys: \n{}\n", fmt::join(inputs.keys, "\n"));
        fmt::print("locks: \n{}\n", fmt::join(inputs.locks, "\n"));
        fmt::print("Part I: {}\n", part1::countMatchingPairs(inputs));
    }
    else
    {
        fmt::print("Usage: {} <filename>\n", args[0]);
    }
    return 0;
}