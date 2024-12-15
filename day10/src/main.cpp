
#include "input.h"

#include "util/util.h"
#include "util/position.h"

#include <range/v3/all.hpp>

#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace aoc2024::day10
{
using Map = std::vector<std::string>;
namespace position = util::position;
using Position = util::position::Position;

bool inBounds(const Map& map, const Position& position)
{
    return position.y >= 0 && position.y < std::ssize(map) && position.x >= 0
           && position.x < std::ssize(map[0]);
}

auto value(const Map& map, const Position& position)
{
    return map[position.y][position.x];
}
namespace part1
{

int solve(const Map& map)
{
    using namespace ::ranges;
    using RouteStartTracker = std::unordered_set<Position>;
    using WorkStep = std::unordered_map<Position, RouteStartTracker>;
    auto currentStep = [&]
    {
        return position::all(std::ssize(map), std::ssize(map[0]))
               | views::filter(std::bind_front(std::equal_to{}, '0'),
                               std::bind_front(value, std::cref(map)))
               | views::transform(
                   [](const auto& pos) -> WorkStep::value_type
                   {
                       return {pos, {pos}};
                   })
               | to<WorkStep>;
    }();

    for (auto i = '1'; i <= '9'; ++i)
    {
        auto nextMoves =
            views::cartesian_product(currentStep, util::position::directions)  //
            | views::transform(
                [](const auto& pair) -> WorkStep::value_type
                {
                    const auto& [pos, dir] = pair;
                    return {pos.first + dir, pos.second};
                })
            | views::filter(std::bind_front(inBounds, std::cref(map)),
                            &WorkStep::value_type::first)
            | views::filter(
                [&](const auto& val)
                {
                    return value(map, val.first) == i;
                });

        WorkStep nextStep;
        for (const auto& [position, routeSources] : nextMoves)
            nextStep[position].insert(std::begin(routeSources), std::end(routeSources));

        currentStep = std::move(nextStep);
    }
    return accumulate(currentStep | views::values, 0, std::plus{}, &RouteStartTracker::size);
}
void test()
{
    {
        Map test{
            "89010123",
            "78121874",
            "87430965",
            "96549874",
            "45678903",
            "32019012",
            "01329801",
            "10456732",
        };
        auto solution = solve(test);
        std::print("Part I Test 1: {}\n", solution);
        assert(solution == 36);
    }
    {
        Map test{
            "..90..9",
            "...1.98",
            "...2..7",
            "6543456",
            "765.987",
            "876....",
            "987....",
        };
        auto solution = solve(test);
        std::print("Part I Test 2: {}\n", solution);
        assert(solution == 4);
    }
    {
        Map test{
            "...0...",
            "...1...",
            "...2...",
            "6543456",
            "7.....7",
            "8.....8",
            "9.....9",
        };
        auto solution = solve(test);
        std::print("Part I Test 3: {}\n", solution);
        assert(solution == 2);
    }
}

void solution()
{
    std::print("Part I: {}\n", solve(input()));  // 531
}
}  // namespace part1

namespace part2
{

int solve(const Map& map)
{
    using namespace ::ranges;
    using WorkStep = std::unordered_map<Position, int>;

    auto currentStep = [&]
    {
        return position::all(std::ssize(map), std::ssize(map[0]))
               | views::filter(std::bind_front(std::equal_to{}, '0'),
                               std::bind_front(value, std::cref(map)))
               | views::transform(
                   [](const auto& pos) -> WorkStep::value_type
                   {
                       return {pos, 1};
                   })
               | to<WorkStep>;
    }();

    for (auto i = '1'; i <= '9'; ++i)
    {
        auto nextMoves =
            views::cartesian_product(currentStep, util::position::directions)  //
            | views::transform(
                [](const auto& pair) -> WorkStep::value_type
                {
                    const auto& [pos, dir] = pair;
                    return {pos.first + dir, pos.second};
                })
            | views::filter(std::bind_front(inBounds, std::cref(map)),
                            &WorkStep::value_type::first)
            | views::filter(
                [&](const auto& val)
                {
                    return value(map, val.first) == i;
                });

        WorkStep nextStep;
        for (const auto& [position, counter] : nextMoves)
            nextStep[position] += counter;

        currentStep = std::move(nextStep);
    }
    return accumulate(currentStep | views::values, 0, std::plus{});
}

void test()
{
    {
        Map test{
            "89010123",
            "78121874",
            "87430965",
            "96549874",
            "45678903",
            "32019012",
            "01329801",
            "10456732",
        };
        auto solution = solve(test);
        std::print("Part II Test 1: {}\n", solution);
        assert(solution == 81);
    }
}
void solution()
{
    std::print("Part II: {}\n", solve(input()));  // 1210
}
}  // namespace part2
}  // namespace aoc2024::day10

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day10;
    part1::test();
    util::withTimer("part1::solution", part1::solution);
    part2::test();
    util::withTimer("part2::solution", part2::solution);
}