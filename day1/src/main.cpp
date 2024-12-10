#include "input.h"

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
    assert(left.size() == right.size());
    std::ranges::sort(left);
    std::ranges::sort(right);
    return std::ranges::fold_left(  //
        std::views::zip(left, right),
        0,
        [](int acc, const auto& val)
        {
            return acc + std::abs(std::get<0>(val) - std::get<1>(val));
        });
}

int test1()
{
    std::vector<int> right = {4, 5, 6};
    return solve({3, 4, 2, 1, 3, 3}, {4, 3, 5, 3, 9, 3});
}
int task()
{
    return solve(left, right);
}

}  // namespace part1
namespace part2
{
int solve(const std::vector<int>& left, const std::vector<int>& right)
{
    assert(left.size() == right.size());
    std::unordered_map<int, int> rightFrequencies;
    for (auto val : right)
        rightFrequencies[val]++;

    return std::ranges::fold_left(  //
        left,
        0,
        [&rightFrequencies](int acc, auto val)
        {
            return acc + rightFrequencies[val] * val;
        });
}

int test1()
{
    std::vector<int> right = {4, 5, 6};
    return solve({3, 4, 2, 1, 3, 3}, {4, 3, 5, 3, 9, 3});
}
int task()
{
    return solve(left, right);
}
}  // namespace part2
}  // namespace aoc2024::day1

int main()
{
    using namespace aoc2024::day1;
    std::print("1. Test 1: {}\n", part1::test1());
    std::print("1. Task: {}\n", part1::task());
    std::print("2. Test 1: {}\n", part2::test1());
    std::print("2. Task: {}\n", part2::task());
    return 0;
}
