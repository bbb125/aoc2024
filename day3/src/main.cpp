#include "input.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <print>
#include <ranges>
#include <regex>
#include <string_view>

namespace aoc2024::day3
{
namespace part1
{
int solve(std::string_view input)
{
    std::regex pattern{R"(mul\((\d{1,3}),(\d{1,3})\))"};
    namespace rng = std::ranges;
    return rng::fold_left(  //
        rng::subrange{std::cregex_iterator{std::begin(input), std::end(input), pattern},
                      std::cregex_iterator{}}
            | std::views::transform(
                [](const auto& match)
                {
                    return std::stoi(match[1].str()) * std::stoi(match[2].str());
                }),
        0,
        std::plus{});
}

void test()
{
    constexpr auto input =
        R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))";
    assert(solve(input) == 161);
    assert(solve(R"(mumumul(2,2)mul(123456,123)mul(100,100))") == 10004);
}
}  // namespace part1

namespace part2
{
int solve(std::string_view input)
{
    enum class State
    {
        Do,
        Dont,
    };

    std::regex pattern{R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))"};
    std::ranges::subrange matches{
        std::cregex_iterator{std::begin(input), std::end(input), pattern},
        std::cregex_iterator{}  //
    };

    int result = 0;
    for (State state = State::Do; const auto& match : matches)
    {
        auto strValue = match.str();
        if (strValue == "do()")
            state = State::Do;
        else if (strValue == "don't()")
            state = State::Dont;
        else if (state == State::Do)  // it's mul
            result += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }
    return result;
}

void test()
{
    constexpr auto input =
        R"(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    assert(solve(input) == 48);
    assert(solve(R"(mumumul(2,2)mul(123456,123)mul(100,100))") == 10004);
}
}  // namespace part2
}  // namespace aoc2024::day3
int main()
{
    using namespace aoc2024::day3;
    part1::test();
    std::print("{}\n", part1::solve(input));
    part2::test();
    std::print("{}\n", part2::solve(input));
}