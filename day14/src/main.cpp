#include "input.h"

#include "util/position.h"
#include "util/functional.h"

#include <range/v3/all.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <ctre.hpp>

#include <cassert>
#include <vector>
#include <string_view>
#include <unordered_set>
#include <iostream>

namespace aoc2024::day14
{
namespace position = aoc2024::util::position;

constexpr std::string_view testInput = R"(p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3)";

struct Robot
{
    position::Position position;
    position::Delta velocity;
};

auto format_as(const Robot& robot)
{
    return std::tie(robot.position, robot.velocity);
}

using Dimension = std::pair<int, int>;

void move(Robot& robot, const Dimension& dimension, int steps)
{
    robot.position += position::Delta{robot.velocity.first * steps,
                                      robot.velocity.second * steps};

    robot.position.x = robot.position.x >= dimension.second
                           ? robot.position.x % dimension.second
                           : robot.position.x;

    robot.position.x =
        robot.position.x < 0
            ? (dimension.second - (std::abs(robot.position.x) % dimension.second))
                  % dimension.second
            : robot.position.x;

    robot.position.y = robot.position.y >= dimension.first
                           ? robot.position.y % dimension.first
                           : robot.position.y;
    robot.position.y =
        robot.position.y < 0
            ? (dimension.first - (std::abs(robot.position.y) % dimension.first))
                  % dimension.first
            : robot.position.y;
}

std::vector<Robot> parse(std::string_view input)
{
    using namespace ::ranges;
    return input | views::split('\n')
           | views::transform(
               [](auto&& line_range)
               {
                   return std::string_view(&*line_range.begin(), distance(line_range));
               })
           | views::filter(std::not_fn(&std::string_view::empty))
           | views::transform(
               [](auto&& line)
               {
                   auto [whole, posX, posY, velX, velY] =
                       ctre::match<R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))">(line);
                   return Robot{
                       .position = {posY.to_number(), posX.to_number()},
                       .velocity = {velY.to_number(), velX.to_number()},
                   };
               })
           | to<std::vector>;
}

void move(std::span<Robot> input, const Dimension& dim, int times)
{
    for (auto& robot : input)
        move(robot, dim, times);
}

using Map = std::vector<std::string>;

Map debug(const std::vector<Robot>& input, const Dimension& dim)
{
    Map result(dim.first, std::string(dim.second, '.'));
    for (const auto& robot : input)
    {
        auto& res = result[robot.position.y][robot.position.x];
        res = res == '.' ? '1' : res + 1;
    }
    return result;
}

namespace part1
{
struct Square
{
    position::Position leftTop;
    position::Position rightBottom;
};
bool belongsBetween(const Robot& robot, const Square& square)
{
    return robot.position.x >= square.leftTop.x
           && robot.position.y >= square.leftTop.y
           && robot.position.x < square.rightBottom.x
           && robot.position.y < square.rightBottom.y;
}

std::uint64_t solve(std::vector<Robot> input, const Dimension& dim, int seconds)
{
    using namespace ::ranges;
    move(input, dim, seconds);
    // 7 11 - 3 5
    auto squares = std::to_array({
        Square{.leftTop = {0, 0}, .rightBottom = {dim.first / 2, dim.second / 2}},
        Square{.leftTop = {0, dim.second / 2 + 1},
               .rightBottom = {dim.first / 2, dim.second}},
        Square{.leftTop = {dim.first / 2 + 1, 0},
               .rightBottom = {dim.first, dim.second / 2}},
        Square{.leftTop = {dim.first / 2 + 1, dim.second / 2 + 1},
               .rightBottom = {dim.first, dim.second}}  //
    });
    return accumulate(squares,
                      1,
                      std::multiplies<>{},
                      [&](const auto& square)
                      {
                          return count_if(input, bind_back(belongsBetween, square));
                      });
}

void test()
{
    using namespace ::ranges;
    auto input = parse(testInput);
    fmt::print("{}\n", input | views::transform(&Robot::position));
    assert(input.size() == 12);
    fmt::print("{}\n", solve(input, {7, 11}, 100));
    assert(solve(input, {7, 11}, 100) == 12);
}

void solution()
{
    auto input = parse(aoc2024::day14::input);
    auto solution = solve(std::move(input), {103, 101}, 100);
    fmt::print("Part I: {}\n", solution);
    assert(224357412);
}
}  // namespace part1

namespace part2
{
void solution()
{
    using namespace ::ranges;
    auto input = parse(aoc2024::day14::input);
    Dimension dim{103, 101};
    std::string current;
    std::unordered_set<std::string> seen;

    auto accumulate = [](const auto& range, auto group)
    {
        auto one = util::functional::constant(std::uint64_t{1});
        return ::ranges::accumulate(range | views::chunk_by(group), 0, std::plus{}, one);
    };
    // 22090 - a loop found using hashes - no point to look further
    // using histogram found one example  17485: 161, 174

    // Christmas tree appears every 10403 seconds
    // 7082: 234, 238

    // 17485: 234, 238
    // 27888: 234, 238
    // 38291: 234, 238
    // 48694: 234, 238
    // 59097: 234, 238
    for (std::size_t i = 1;; ++i)
    {
        move(input, dim, 1);

        auto x = input | views::transform(&Robot::position) | to_vector;
        auto y = input | views::transform(&Robot::position) | to_vector;
        x |= actions::sort(position::lessByX);
        y |= actions::sort(position::lessByY);
        auto countX = accumulate(x, position::followedByX);
        auto countY = accumulate(y, position::followedByY);
        if (countX < 420 || countY < 420)
        {
            fmt::print("{}: {}, {}\n", i, countY, countX);
            fmt::print("{}\n", fmt::join(debug(input, dim), "\n"));
            break;
        }
    }
}
}  // namespace part2
}  //   namespace aoc2024::day14
int main()
{
    using namespace aoc2024::day14;
    part1::test();
    part1::solution();
    part2::solution();
    return 0;
}