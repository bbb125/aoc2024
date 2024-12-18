#include "input.h"
#include "util/map.h"
#include "util/position.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <utility>
#include <vector>
#include <string>
#include <unordered_set>

namespace aoc2024::day18
{
namespace position = util::position;
std::vector<position::Position> testInput{
    {4, 5}, {2, 4}, {5, 4}, {0, 3}, {1, 2}, {3, 6}, {4, 2}, {5, 1}, {6, 0},
    {3, 3}, {6, 2}, {1, 5}, {2, 1}, {5, 5}, {5, 2}, {5, 6}, {4, 1}, {4, 0},
    {4, 6}, {1, 1}, {1, 6}, {0, 1}, {5, 0}, {6, 1}, {0, 2},
};
using Dim = std::pair<int, int>;
constexpr Dim testDim{7, 7};

position::Map generateMap(std::span<const position::Position> fallingBytes,
                          int numberOfBytes,
                          Dim dim)
{
    using namespace ::ranges;
    position::MapData map(dim.first, std::string(dim.second, '.'));
    for (auto [y, x] : fallingBytes | views::take(numberOfBytes))
        map[y][x] = '#';

    return map;
}


struct Maze
{
    Maze(position::Map data)
        : start{0, 0}
        , end{data.height() - 1, data.width() - 1}
        , map{std::move(data)}
    {}


    constexpr bool canMove(const position::Position& pos) const
    {
        return map.inBounds(pos) && map.value(pos) != '#';
    }

    std::optional<std::size_t> search() const
    {
        using namespace ::ranges;
        using HeapElement = std::pair<std::size_t, position::Position>;  // cost, pos

        std::deque<HeapElement> queue{HeapElement{0, start}};

        std::unordered_set<position::Position> visited;  // todo: use bitset if performance issues
        while (!std::empty(queue))
        {
            auto [cost, pos] = queue.front();
            queue.pop_front();

            if (pos == end)
                return cost;

            if (visited.contains(pos))
                continue;

            visited.insert(pos);

            for (const auto& nextPos :
                 position::directions
                     | views::transform(std::bind_front(std::plus{}, pos))
                     | views::filter(std::bind_front(&Maze::canMove, this)))
            {
                auto newCost = cost + 1;
                queue.emplace_back(newCost, nextPos);
            }
        }
        return std::nullopt;
    }

    position::Position start;
    position::Position end;
    position::Map map;
};

namespace part1
{
void test()
{
    Maze maze{generateMap(testInput, 12, testDim)};
    auto solution = maze.search();
    fmt::print("Part I Test: {}\n", *solution);
    assert(solution == 22);
}

void solution()
{
    auto data = input();
    constexpr int numberOfBytes = 1024;
    Dim dim{71, 71};
    Maze maze{generateMap(data, numberOfBytes, dim)};
    auto solution = maze.search();
    fmt::print("Part I Solution: {}\n", *solution);
}
}  // namespace part1

namespace part2
{

int search(std::span<const position::Position> fallingBytes, Dim dim, int start)
{
    int left = start;
    int right = std::ssize(fallingBytes);
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        Maze maze{generateMap(fallingBytes, mid, dim)};
        if (auto solution = maze.search(); !solution)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

// do stupid binary search?
void test()
{
    auto byteNum = search(testInput, testDim, 12);
    fmt::print("Part II Test (index, pos): {}, {}\n", byteNum - 1, testInput[byteNum - 1]);
}

void solution()
{
    auto data = input();
    constexpr Dim dim{71, 71};
    auto byteNum = search(data, dim, 1024);
    fmt::print("Part II Solution (index, pos): {}, {}\n",
               byteNum - 1,
               data[byteNum - 1]);  //  (46, 16)
}
}  // namespace part2
}  // namespace aoc2024::day18

int main()
{
    using namespace aoc2024::day18;
    part1::test();
    part1::solution();
    part2::test();
    part2::solution();
    //    Part I Test: 22
    //    Input size: 3450Part I Solution: 310
    //    Part II Test (index, pos): 20, (1, 6)
    //    Part II Solution (index, pos): 3045, (46, 16)
}