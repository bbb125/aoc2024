#include "input.h"

#include "util/position.h"
#include "util/map.h"

#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <deque>
#include <unordered_set>
#include <mdspan>

namespace aoc2024::day16
{
namespace position = aoc2024::util::position;
struct Maze
{
    Maze(position::MapData data)
        : map{std::move(data)}
    {
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

    static constexpr std::size_t maxSize = 1000;

    constexpr bool canMove(const position::Position& pos) const
    {
        return map.inBounds(pos) && map.value(pos) != '#';
    }

    // feels like backtracking is ugly
    std::pair<std::size_t, std::size_t> searchWithTracking()
    {
        using namespace ::ranges;
        struct HeapElement
        {
            std::size_t cost = 0;
            position::Position pos;
            position::DirectionIndex direction;
        };

        std::deque<HeapElement> heap{HeapElement{0, start, startDirection}};

        auto [height, width] = map.dim();
        struct BacktrackingData
        {
            std::size_t cost = std::numeric_limits<std::size_t>::max();
            std::unordered_set<position::Position> parents;
        };
        std::vector<BacktrackingData> backtrackStorage(height * width * 4);
        auto backTrack = std::mdspan{backtrackStorage.data(), height, width, 4};

        while (!std::empty(heap))
        {
            auto element = heap.front();
            pop_heap(heap, std::greater{}, &HeapElement::cost);
            heap.pop_back();

            auto& backTrackRecord = backTrack[element.pos.y,
                                              element.pos.x,
                                              position::toIndex(element.direction)];
            if (element.pos == end)
                return {element.cost, backTrackRecord.parents.size() + 1};


            for (const auto& [dirIndex, dirCost] : {
                     std::pair{element.direction, 0},
                     std::pair{position::turnRight(element.direction), 1000},
                     std::pair{position::turnLeft(element.direction), 1000},  //
                 })
            {
                auto nextPos = element.pos
                               + position::directions[position::toIndex(dirIndex)];

                if (!canMove(nextPos))
                    continue;

                auto newCost = element.cost + dirCost + 1;

                if (newCost < backTrack[nextPos.y, nextPos.x, position::toIndex(dirIndex)]
                                  .cost)
                {
                    std::unordered_set<position::Position> parent{element.pos};

                    parent.insert(std::begin(backTrackRecord.parents),
                                  std::end(backTrackRecord.parents));
                    backTrack[nextPos.y, nextPos.x, position::toIndex(dirIndex)] =
                        BacktrackingData{
                            .cost = newCost,
                            .parents = std::move(parent),
                        };

                    heap.emplace_back(newCost, nextPos, dirIndex);
                    push_heap(heap, std::greater{}, &HeapElement::cost);  // not needed
                }
                else if (newCost
                         == backTrack[nextPos.y, nextPos.x, position::toIndex(dirIndex)]
                                .cost)
                {
                    backTrack[nextPos.y, nextPos.x, position::toIndex(dirIndex)]
                        .parents.insert(element.pos);
                    backTrack[nextPos.y, nextPos.x, position::toIndex(dirIndex)]
                        .parents.insert(std::begin(backTrackRecord.parents),
                                        std::end(backTrackRecord.parents));
                }
            }
        }


        return {};
    }


    position::Position start;
    position::DirectionIndex startDirection = position::DirectionIndex::Right;
    position::Position end;
    position::Map map;
};

position::MapData testData1{
    //
    "###############",
    "#.......#....E#",
    "#.#.###.#.###.#",
    "#.....#.#...#.#",
    "#.###.#####.#.#",
    "#.#.#.......#.#",
    "#.#.#####.###.#",
    "#...........#.#",
    "###.#.#####.#.#",
    "#...#.....#.#.#",
    "#.#.#.###.#.#.#",
    "#.....#...#.#.#",
    "#.###.#.#.#.#.#",
    "#S..#.....#...#",
    "###############",
};

position::MapData testData2{
    "#################",
    "#...#...#...#..E#",
    "#.#.#.#.#.#.#.#.#",
    "#.#.#.#...#...#.#",
    "#.#.#.#.###.#.#.#",
    "#...#.#.#.....#.#",
    "#.#.#.#.#.#####.#",
    "#.#...#.#.#.....#",
    "#.#.#####.#.###.#",
    "#.#.#.......#...#",
    "#.#.###.#####.###",
    "#.#.#...#.....#.#",
    "#.#.#.#####.###.#",
    "#.#.#.........#.#",
    "#.#.#.#########.#",
    "#S#.............#",
    "#################",
};
namespace part1
{

void test()
{
    {
        Maze maze{testData1};
        auto [cost, cells] = maze.searchWithTracking();
        fmt::print("Part I Test 1: {}\n", cost);
        assert(cost == 7036);
    }
    {
        Maze maze{testData2};
        auto [cost, cells] = maze.searchWithTracking();
        fmt::print("Part I Test 2: {}\n", cost);
        assert(cost == 11048);
    }
}

void solution()
{
    Maze maze{input()};
    auto [cost, cells] = maze.searchWithTracking();
    fmt::print("Part I Solution: {}\n", cost);
}

}  // namespace part1

namespace part2
{

void test()
{
    {
        Maze maze{testData1};
        auto [cost, cells] = maze.searchWithTracking();
        fmt::print("Part II Test 1: {}\n", cells);
        assert(cells == 45);
    }
    {
        Maze maze{testData2};
        auto [cost, cells] = maze.searchWithTracking();
        fmt::print("Part II Test 2: {}\n", cells);
        assert(cells == 64);
    }
}

void solution()
{
    Maze maze{input()};
    auto [cost, cells] = maze.searchWithTracking();
    fmt::print("Part II Solution: {}\n", cells); // 502
}
}  // namespace part2
}  // namespace aoc2024::day16

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day16;
    part1::test();
    part1::solution();
    part2::test();
    part2::solution();
    return 0;
}