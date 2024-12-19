#include "input.h"

#include "util/util.h"

#include <fmt/format.h>

#include <range/v3/all.hpp>

#include <cassert>
#include <vector>
#include <string>
#include <unordered_set>
namespace aoc2024::day19
{
std::vector<std::string> testTowels{"r", "wr", "b", "g", "bwu", "rb", "gb", "br"};
std::vector<std::string> testPattern{
    "brwrr",
    "bggr",
    "gbbr",
    "rrbgbr",
    "ubwu",
    "bwurrg",
    "brgr",
    "bbrgwb",
};

struct PreprocessedTowels
{
    std::size_t maxSize;
    using Towels = std::unordered_set<std::string_view>;
    using BySize = std::vector<Towels>;
    BySize towels;
};

PreprocessedTowels preprocessTowels(std::span<const std::string> towels)
{
    PreprocessedTowels::BySize result;
    for (const auto& towel : towels)
    {
        if (towel.size() >= result.size())
            result.resize(towel.size() + 1);
        result[towel.size()].insert(towel);
    }
    return {std::size(result), std::move(result)};
}

struct Matcher
{
    Matcher(std::span<const std::string> towels)
        : preprocessedTowels{preprocessTowels(towels)}
    {}

    std::uint64_t operator()(std::string_view pattern)
    {
        using namespace ::ranges;
        if (pattern.length() == 0)
            return 1;

        if (cache.contains(pattern))
            return cache[pattern];

        std::uint64_t counter = 0;
        for (std::size_t i = 1;
             i <= std::min(preprocessedTowels.maxSize - 1, pattern.size());
             ++i)
        {
            std::string_view left = pattern.substr(0, i);
            std::string_view right = pattern.substr(i);
            if (preprocessedTowels.towels[i].contains(left))
                counter += (*this)(right);
        }
        cache[pattern] = counter;
        return counter;
    }
    PreprocessedTowels preprocessedTowels;
    mutable std::unordered_map<std::string_view, std::uint64_t> cache;
};

namespace part1
{

void test()
{
    Matcher matcher{testTowels};
    for (const auto& pattern : testPattern)
        fmt::print("{}: {}\n", pattern, matcher(pattern) != 0);
}

void solution()
{
    using namespace ::ranges;
    auto inputTowels = towels();
    int count = 0;
    Matcher matcher{inputTowels};
    for (const auto& pattern : patterns())
    {
        if (matcher(pattern) != 0)
        {
            fmt::print("{}\n", pattern);
            ++count;
        }
    }
    fmt::print("Part I Solution: {}\n", count);
    assert(count == 374);
}
}  // namespace part1

namespace part2
{

void test()
{
    std::uint64_t counter = 0;
    Matcher matcher{testTowels};
    for (const auto& pattern : testPattern)
    {
        auto matches = matcher(pattern);
        fmt::print("{}: {}\n", pattern, matches);
        counter += matches;
    }
    assert(counter == 16);
    fmt::print("{}\n", counter);
}

void solution()
{
    using namespace ::ranges;
    auto inputTowels = towels();
    Matcher matcher{inputTowels};
    auto result = accumulate(patterns(), std::uint64_t{0}, std::plus{}, matcher);
    fmt::print("Part I Solution: {}\n", result);
    assert(result == 1100663950563322);
}
}  // namespace part2
}  // namespace aoc2024::day19

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day19;
    part1::test();
    part1::solution();
    part2::test();
    util::withTimer("part2::solution", part2::solution);
}