#include "input.h"

#include "util/util.h"
#include "util/functional.h"
#include "util/map.h"
#include "util/position.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <vector>
#include <map>

namespace aoc2024::day20
{
namespace position = aoc2024::util::position;
position::MapData testInput{
    "###############",
    "#...#...#.....#",
    "#.#.#.#.#.###.#",
    "#S#...#.#.#...#",
    "#######.#.#.###",
    "#######.#.#...#",
    "#######.#.###.#",
    "###..E#...#...#",
    "###.#######.###",
    "#...###...#...#",
    "#.#####.#.###.#",
    "#.#...#.#.#...#",
    "#.#.#.#.#.#.###",
    "#...#...#...###",
    "###############",
};


struct Maze
{
    using Distances = std::vector<std::vector<std::uint64_t>>;

    Maze(position::MapData data)
        : map{std::move(data)}
    {
        using namespace ::ranges;
        for (const auto& pos : map.all())
        {
            auto& val = map.value(pos);
            if (val == 'S')
            {
                start = pos;
                val = '.';
            }
            else if (val == 'E')
            {
                end = pos;
                val = '.';
            }
        }
    }

    void calcDistancesFrom(const position::Position& startPos, Distances& output)
    {
        using namespace ::ranges;
        using HeapElement = std::pair<std::size_t, position::Position>;  // cost, pos

        std::deque<HeapElement> queue{HeapElement{0, startPos}};

        auto visited = [&](const auto& pos)
        {
            return output[pos.y][pos.x] != maxDistance;
        };
        auto canMove = [&](const auto& pos)
        {
            return map.inBounds(pos) && map.value(pos) != '#';
        };

        while (!std::empty(queue))
        {
            pop_heap(queue, std::greater{}, &HeapElement::first);
            auto [currentCost, currentPos] = queue.back();
            queue.pop_back();

            if (visited(currentPos))
                continue;

            output[currentPos.y][currentPos.x] = currentCost;

            queue |= actions::push_back(
                position::directions
                | views::transform(std::bind_front(std::plus{}, currentPos))
                | views::filter(std::not_fn(visited)) | views::filter(canMove)
                | views::transform(
                    [&](const auto& pos)
                    {
                        return HeapElement{currentCost + 1, pos};
                    }));
            push_heap(queue, std::greater{}, &HeapElement::first);
        }
    }

    std::uint64_t solve(std::size_t expectedImprovement,
                        std::uint64_t maxCheatLength = 1)
    {
        using namespace ::ranges;
        calcDistancesFrom(start, distanceFromStart);
        calcDistancesFrom(end, distanceFromEnd);

        auto noSavings = distanceFromStart[end.y][end.x];
        std::uint64_t result = 0;
        std::map<std::uint64_t, std::uint64_t> improvements;
        auto notWall = [&](const auto& pos)
        {
            return map.value(pos) != '#';
        };
        auto positionsToCheck =
            views::cartesian_product(map.all() | views::filter(notWall),
                                     map.all() | views::filter(notWall))
            | views::transform(
                [](const auto& positions)
                {
                    const auto& [pos1, pos2] = positions;
                    return std::tuple{pos1,
                                      pos2,
                                      static_cast<std::uint64_t>(
                                          std::abs(pos1.x - pos2.x)
                                          + std::abs(pos1.y - pos2.y))};
                });

        for (const auto& [pos1, pos2, manhattanDistance] : positionsToCheck)
        {
            if (manhattanDistance <= maxCheatLength)
            {
                auto distance = distanceFromStart[pos1.y][pos1.x]
                                + distanceFromEnd[pos2.y][pos2.x] + manhattanDistance;

                if (distance < noSavings)  // debug
                    ++improvements[noSavings - distance];

                result += (distance < noSavings
                           && (noSavings - distance) >= expectedImprovement);
            }
        }
        fmt::print("Debug: improvements - {}\n", improvements);

        return result;
    }

    position::Map map;
    position::Position start;
    position::Position end;

    static constexpr auto maxDistance = std::numeric_limits<std::uint64_t>::max();
    Distances distanceFromStart{static_cast<std::size_t>(map.height()),
                                std::vector<std::uint64_t>(map.width(), maxDistance)};
    Distances distanceFromEnd{static_cast<std::size_t>(map.height()),
                              std::vector<std::uint64_t>(map.width(), maxDistance)};
};


namespace part1
{
void test()
{
    Maze maze{testInput};
    auto solution = maze.solve(1, /*means 1*/ 2);
    fmt::print("Part I Test: {}\n", solution);
}

void solution()
{
    Maze maze{input()};
    auto solution = maze.solve(100, 2);
    fmt::print("Part I Solution: {}\n", solution);  // 1395
}
}  // namespace part1

namespace part2
{
void test()
{
    Maze maze{testInput};
    auto solution = maze.solve(50, 20);
    fmt::print("Part II Test: {}\n", solution);
}
void solution()
{
    Maze maze{input()};
    auto solution = maze.solve(100, 20);
    fmt::print("Part II Solution: {}\n", solution);
    assert(solution == 993178);
}
}  // namespace part2
}  // namespace aoc2024::day20

int main()
{
    using namespace aoc2024::day20;
    part1::test();
    aoc2024::util::withTimer("part1::solution", part1::solution);  // 4719 too high
    part2::test();
    aoc2024::util::withTimer("part2::solution", part2::solution);
    return 0;
}