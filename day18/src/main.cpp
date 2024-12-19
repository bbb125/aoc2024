#include "input.h"
#include "util/util.h"
#include "util/map.h"
#include "util/position.h"
#include "util/functional.h"

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


template <typename Predicate>
std::optional<std::size_t> dijkstraMazeSearch(const position::Position& start,
                                              const position::Position& end,
                                              Predicate canMove)
{
    using namespace ::ranges;
    using HeapElement = std::pair<std::size_t, position::Position>;  // cost, pos

    std::vector<HeapElement> queue{HeapElement{0, start}};

    using Visited = std::unordered_set<position::Position>;
    Visited visited;  // todo: use bitset if performance issues
    while (!std::empty(queue))
    {
        pop_heap(queue, std::greater{}, &HeapElement::first);
        auto [currentCost, currentPos] = queue.back();
        queue.pop_back();

        if (currentPos == end)
            return currentCost;

        if (visited.contains(currentPos))
            continue;

        visited.insert(currentPos);

        for (const auto& nextPos :
             position::directions
                 | views::transform(std::bind_front(std::plus{}, currentPos))
                 | views::filter(
                     [&visited](const auto& pos)
                     {
                         return !visited.contains(pos);
                     })
                 | views::filter(canMove))
        {
            queue.emplace_back(currentCost + 1, nextPos);
            push_heap(queue, std::greater{}, &HeapElement::first);
        }
    }
    return std::nullopt;
}

auto makeCanMode(std::span<const position::Position> fallingBytes, int numberOfBytes, Dim dim)
{
    return [map = generateMap(fallingBytes, numberOfBytes, dim)](const auto& pos)
    {
        return map.inBounds(pos) && map.value(pos) != '#';
    };
}

namespace part1
{
void test()
{
    auto solution = dijkstraMazeSearch(  //
        {0, 0},
        {testDim.first - 1, testDim.second - 1},
        makeCanMode(testInput, 12, testDim));
    fmt::print("Part I Test: {}\n", *solution);
    assert(solution == 22);
}

void solution()
{
    auto data = input();
    constexpr int numberOfBytes = 1024;
    Dim dim{71, 71};
    auto solution = dijkstraMazeSearch(  //
        {0, 0},
        {dim.first - 1, dim.second - 1},
        makeCanMode(data, numberOfBytes, dim));
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
        auto solution = dijkstraMazeSearch(  //
            {0, 0},
            {dim.first - 1, dim.second - 1},
            makeCanMode(fallingBytes, mid, dim));
        if (!solution)
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
    aoc2024::util::withTimer("part2::solution", part2::solution);
    //    Part I Test: 22
    //    Input size: 3450Part I Solution: 310
    //    Part II Test (index, pos): 20, (1, 6)
    //    Part II Solution (index, pos): 3045, (46, 16)
}