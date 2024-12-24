#include <range/v3/all.hpp>

#include <iostream>
#include <span>
#include <cassert>

namespace aoc2024::day2
{

int direction(std::span<const int> report)
{
    // would be nice to use std::views::slide, but it's unavailable
    int increase = 0;
    for (std::size_t i = 0; i < std::size(report) - 1; ++i)
        increase += report[i + 1] > report[i] ? 1 : -1;

    return increase >= 0 ? 1 : -1;
}

auto findReportBreak(std::span<const int> report, int sign, int minThreshold, int maxThreshold)
{
    // find max difference between consecutive elements
    return ::ranges::adjacent_find(  //
        report,
        [sign, minThreshold, maxThreshold](int a, int b)
        {
            return sign * (b - a) > maxThreshold || sign * (b - a) < minThreshold;
        });
}
namespace part1
{
//
bool isReportSafe(std::span<const int> report, int minThreshold, int maxThreshold)
{
    assert(std::size(report) > 1);
    return findReportBreak(report, direction(report), minThreshold, maxThreshold)
           == std::end(report);
}

int solution(const std::vector<std::vector<int>>& inputs)
{
    using namespace ::ranges;

    return count_if(inputs, bind_back(isReportSafe, 1, 3));
}

void test()
{
    std::vector<std::vector<int>> inputs{{7, 6, 4, 2, 1},
                                         {1, 2, 7, 8, 9},
                                         {9, 7, 6, 2, 1},
                                         {1, 3, 2, 4, 5},
                                         {8, 6, 4, 4, 1},
                                         {1, 3, 6, 7, 9}};

    std::print("Part 1 test: {}\n", solution(inputs));
}
}  // namespace part1

namespace part2
{
bool isReportSafe(const std::vector<int>& report, int minThreshold, int maxThreshold)
{
    using namespace ::ranges;
    assert(std::size(report) > 1);

    int sign = direction(report);

    auto validate = bind_back(findReportBreak, sign, minThreshold, maxThreshold);

    auto it = validate(report);
    if (it == std::end(report))
        return true;

    // let's do some ugly shit -- brute force the element we want to delete
    auto index = distance(std::begin(report), it);
    if (index != 0)
        --index;
    for (std::size_t i = 0; i < 3 && index + i < std::size(report); ++i)
    {
        auto alternative = report;
        alternative.erase(std::next(std::begin(alternative), index + i));

        if (validate(alternative) == std::end(alternative))
            return true;
    }
    return false;
}


int solution(const std::vector<std::vector<int>>& inputs)
{
    using namespace ::ranges;
    return count_if(inputs, bind_back(isReportSafe, 1, 3));
}

void test()
{
    std::vector<std::vector<int>> inputs{{7, 6, 4, 2, 1},
                                         {1, 2, 7, 8, 9},
                                         {9, 7, 6, 2, 1},
                                         {1, 3, 2, 4, 5},
                                         {8, 6, 4, 4, 1},
                                         {1, 3, 6, 7, 9}};
    using namespace ::ranges;
    std::print("Part II testL: {}\n", count_if(inputs, bind_back(isReportSafe, 1, 3)));
}
}  // namespace part2
}  // namespace aoc2024::day2

int main()
{
    using namespace aoc2024::day2;
    part1::test();
    part2::test();
    return 0;
}
