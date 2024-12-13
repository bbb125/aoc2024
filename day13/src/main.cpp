#include "input.h"

#include "util/functional.h"

#include <range/v3/all.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cstdlib>
#include <string>
#include <string_view>
#include <regex>

namespace aoc2024::day13
{
//

struct Input
{
    using Point = std::pair<std::int64_t, std::int64_t>;
    Point A;
    Point B;
    Point prize;
};

auto format_as(const Input& input)
{
    return std::tie(input.A, input.B, input.prize);
}

std::vector<Input> parse(std::string_view input)
{
    using namespace ::ranges;
    std::regex patternAB{R"(Button [AB]: X\+(\d+), Y\+(\d+))"};
    std::regex patternPrize{R"(Prize: X=(\d+), Y=(\d+))"};
    auto parsePoint = [](std::string_view line, std::regex pattern) -> Input::Point
    {
        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_search(line.begin(), line.end(), match, pattern))
        {
            auto x = std::stoll(std::string(match[1].first, match[1].second));
            auto y = std::stoll(std::string(match[2].first, match[2].second));
            return {x, y};
        }
        std::unreachable();
    };
    return input | views::split('\n')
           | views::transform(
               [](auto&& line_range)
               {
                   return std::string_view(&*line_range.begin(), distance(line_range));
               })
           | views::filter(std::not_fn(&std::string_view::empty)) | views::chunk(3)
           | views::transform(
               [&](auto chunk)
               {
                   auto it = std::begin(chunk);
                   return Input{
                       .A = parsePoint(std::string_view{*(it++)}, patternAB),
                       .B = parsePoint(std::string_view{*(it++)}, patternAB),
                       .prize = parsePoint(std::string_view{*(it++)}, patternPrize),
                   };
               })
           | to<std::vector>;
}

std::int64_t solveOne(const Input& input)
{
    const auto& [a, b, prize] = input;
    auto div = a.first * b.second - a.second * b.first;
    if (div == 0)
        return 0;

    auto [Anum, r1] = std::lldiv(prize.first * b.second - prize.second * b.first, div);
    if (r1 != 0)
        return 0;
    auto [Bnum, r2] = std::lldiv(prize.first - Anum * a.first, b.first);
    if (r2 != 0)
        return 0;

    return Anum * 3 + Bnum;
}


std::uint64_t solveAll(std::span<Input> inputs)
{
    return ranges::accumulate(inputs, std::uint64_t{0}, std::plus{}, solveOne);
}

namespace part1
{

void test()
{
    auto input = parse(testInput);
    auto solution = solveAll(input);
    fmt::print("{}\n", input);
    fmt::print("Part I Test: {}\n", solution);  // 480
}

void solution()
{
    auto input = parse(aoc2024::day13::input);

    auto solution = solveAll(input);
    fmt::print("Part I: {}\n", solution);  // 30973
}
}  // namespace part1

namespace part2
{

void solution()
{
    using namespace ::ranges;
    constexpr auto increment = 10'000'000'000'000;
    auto originalInput = parse(aoc2024::day13::input);
    auto input = originalInput
                 | views::transform(
                     [increment](const auto& input)
                     {
                         return Input{.A = input.A,
                                      .B = input.B,
                                      .prize = {input.prize.first + increment,
                                                input.prize.second + increment}};
                     })
                 | to<std::vector>;

    auto solution = solveAll(input);
    fmt::print("Part II: {}\n", solution);
}
}  // namespace part2
}  // namespace aoc2024::day13

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day13;
    part1::test();
    part1::solution();
    part2::solution();
    return 0;
}