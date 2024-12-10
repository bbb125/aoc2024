#include "input.h"
#include "util/util.h"

#include <range/v3/all.hpp>

#include <vector>
#include <cmath>

namespace aoc2024::day7
{


std::vector<Input> testInputs = {
    {190, {10, 19}},
    {3267, {81, 40, 27}},
    {83, {17, 5}},
    {156, {15, 6}},
    {7290, {6, 8, 6, 15}},
    {161011, {16, 10, 13}},
    {192, {17, 8, 14}},
    {21037, {9, 7, 18, 13}},
    {292, {11, 6, 16, 20}},
};
//
namespace part1
{
std::uint64_t solveOne(Input input)
{
    // 5837374519342
    using namespace ::ranges;
    std::uint64_t result = input.result;
    std::vector<std::uint64_t> values = {0};
    auto nextStepFilter = [result = input.result](auto v)
    {
        return v <= result && v != 0;
    };
    for (const auto& value : input.values)
    {
        std::vector<std::uint64_t> newValues;
        newValues.reserve(values.size() * 2);
        newValues |= push_back(  //
            values | views::transform(std::bind_front(std::plus<>{}, value))
            | views::filter(nextStepFilter));
        newValues |= push_back(  //
            values | views::transform(std::bind_front(std::multiplies<>{}, value))
            | views::filter(nextStepFilter));
        values = std::move(newValues);
    }

    return contains(values, result) ? result : 0;
}

std::uint64_t solve(const std::vector<Input>& inputs)
{
    return ::ranges::accumulate(  //
        inputs,
        std::uint64_t{0},
        [](auto acc, const auto& input)
        {
            return acc + solveOne(input);
        });
}
void test()
{
    std::print("{}\n", solve(testInputs));
}

void solution()
{
    std::print("Part I {}\n", solve(inputs()));
}
}  // namespace part1


namespace part2
{
std::uint64_t multiplier(std::uint64_t value)
{
    std::uint64_t result = 1;
    while (value > 0)
    {
        result *= 10;
        value /= 10;
    }
    return result;
}

std::uint64_t solveOne(Input input)
{
    using namespace ::ranges;
    std::uint64_t result = input.result;
    std::vector<std::uint64_t> values = {0};
    values.reserve(std::pow(3, std::size(input.values)));
    auto nextStepFilter = [result = input.result](auto v)
    {
        return v <= result && v != 0;
    };

    std::vector<std::uint64_t> newValues;
    newValues.reserve(values.capacity());
    for (const auto& value : input.values)
    {
        newValues.clear();
        newValues |= push_back(  //
            values | views::transform(std::bind_front(std::plus<>{}, value))
            | views::filter(nextStepFilter));
        newValues |= push_back(  //
            values | views::transform(std::bind_front(std::multiplies<>{}, value))
            | views::filter(nextStepFilter));
        newValues |= push_back(  //
            values
            | views::transform(
                [&value, mult = multiplier(value)](auto v) -> std::uint64_t
                {
                    if (std::numeric_limits<std::uint64_t>::max() / mult < v)
                        return 0;
                    return v * mult + value;
                })
            | views::filter(nextStepFilter));
        values = std::move(newValues);
    }

    return contains(values, result) ? result : 0;
}

std::uint64_t solve(const std::vector<Input>& inputs)
{
    return ::ranges::accumulate(  //
        inputs,
        std::uint64_t{0},
        [](auto acc, const auto& input)
        {
            return acc + solveOne(input);
        });
}

void test()
{
    std::print("{}\n", solve(testInputs));
}

void solution()
{
    std::print("Part II: {}\n", solve(inputs()));
}
}  // namespace part2
}  // namespace aoc2024::day7

int main()
{
    using namespace aoc2024::day7;
    part1::test();
    part1::solution();

    part2::test();
    aoc2024::util::withTimer("part2::solution", part2::solution);
    return 0;
}