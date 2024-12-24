#include <range/v3/all.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cassert>
#include <unordered_map>

namespace aoc2024::day1
{

namespace part1
{
int solve(std::vector<int> left, std::vector<int> right)
{
    using namespace ::ranges;
    assert(left.size() == right.size());
    return accumulate(  //
        views::zip(actions::sort(left), actions::sort(right)),
        0,
        {},
        [](const auto& pair)
        {
            return std::abs(pair.first - pair.second);
        });
}

int test1()
{
    std::vector<int> right = {4, 5, 6};
    return solve({3, 4, 2, 1, 3, 3}, {4, 3, 5, 3, 9, 3});
}

}  // namespace part1
namespace part2
{
int solve(std::span<const int> left, std::span<const int> right)
{
    using namespace ::ranges;
    assert(left.size() == right.size());
    std::unordered_map<int, int> rightFrequencies;
    for (auto val : right)
        rightFrequencies[val]++;

    return accumulate(  //
        left
            | views::transform(
                [&rightFrequencies](auto val)
                {
                    return rightFrequencies[val] * val;
                }),
        0);
}

int test1()
{
    auto left = {3, 4, 2, 1, 3, 3};
    auto right = {4, 3, 5, 3, 9, 3};
    return solve(left, right);
}

}  // namespace part2
}  // namespace aoc2024::day1

int main()
{
    using namespace aoc2024::day1;
    std::print("1. Test 1: {}\n", part1::test1());
    std::print("2. Test 1: {}\n", part2::test1());

    return 0;
}
