#include "input.h"
#include "util/util.h"
#include "util/position.h"
#include "util/functional.h"

#include <range/v3/all.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <vector>
#include <string>
#include <unordered_set>
#include <optional>

namespace aoc2024::day12
{
namespace position = aoc2024::util::position;
using Map = std::vector<std::string>;

constexpr auto inBounds(const Map& input, const position::Position& pos)
{
    return pos.y >= 0 && pos.y < std::ssize(input) && pos.x >= 0
           && pos.x < std::ssize(input[pos.y]);
}

struct Filler
{
    Filler(const Map& input)
        : map{input}
        , seen{std::size(input), std::vector<int>(std::ssize(input), unseen)}
    {}

    void operator()(const position::Position& pos)
    {
        if (seen[pos.y][pos.x] != unseen)
            return;

        fill(pos, areasCount++);
    }

    void recursiveFill(const position::Position& pos, char ch, int filler)
    {
        namespace rng = ::ranges;
        namespace rv = ::ranges::views;
        if (!inBounds(map, pos) || map[pos.y][pos.x] != ch)
            return;

        if (visited(pos, filler))
            return;

        for (const auto& neighbour : position::neighbours(pos))
            recursiveFill(neighbour, ch, filler);
    }

    void fill(const position::Position& pos, int filler)
    {
        namespace rng = ::ranges;
        namespace rv = ::ranges::views;
        std::vector<position::Position> steps{pos};
        markVisited(pos, filler);

        while (!std::empty(steps))
        {
            auto currentPos = steps.back();

            steps.pop_back();

            for (const auto& neighbour : position::neighbours(currentPos))
            {
                if (!inBounds(map, neighbour))
                    continue;
                if (visited(neighbour, filler))
                    continue;

                if (value(neighbour) == value(currentPos))
                {
                    markVisited(neighbour, filler);
                    steps.push_back(neighbour);
                }
            }
        }
    }

    char value(const position::Position& pos) const
    {
        return map[pos.y][pos.x];
    }
    constexpr bool visited(const position::Position& pos, int filler) const
    {
        return seen[pos.y][pos.x] == filler;
    }

    bool markVisited(const position::Position& pos, int filler)
    {
        return seen[pos.y][pos.x] = filler;
    }

    const Map& map;
    int areasCount = 0;
    std::vector<std::vector<int>> seen;
    static constexpr int unseen = -1;
};

std::vector<std::uint64_t> computeSquares(const Filler& filler)
{
    std::vector<std::uint64_t> result(filler.areasCount + 1, 0);
    for (const auto& pos :
         position::all(std::ssize(filler.map), std::ssize(filler.map[0])))
        ++result[filler.seen[pos.y][pos.x]];
    return result;
}

std::vector<std::uint64_t> computePerimeters(const Filler& filler)
{
    std::vector<std::uint64_t> result(filler.areasCount + 1, 0);
    for (const auto& pos :
         position::all(std::ssize(filler.map), std::ssize(filler.map[0])))
    {
        for (const auto& neighbour : position::neighbours(pos))
        {
            result[filler.seen[pos.y][pos.x]] +=
                !inBounds(filler.map, neighbour)
                || filler.seen[pos.y][pos.x]
                       != filler.seen[neighbour.y][neighbour.x];
        }
    }
    return result;
}

std::vector<std::uint64_t> countEdges(const Filler& filler)
{
    using namespace ::ranges;
    const auto& seen = filler.seen;
    const auto& map = filler.map;

    using ByDirection = std::vector<position::Position>;
    std::vector<std::vector<ByDirection>> boundaryCells(  //
        filler.areasCount + 1,
        std::vector<ByDirection>{position::directions.size()});

    for (const auto& pos : position::all(std::size(map), std::size(map[0])))
    {
        for (const auto& [index, neighbour] : position::neighbours(pos) | views::enumerate)
        {
            if (!inBounds(map, neighbour)
                || seen[pos.y][pos.x] != seen[neighbour.y][neighbour.x])
                boundaryCells[seen[pos.y][pos.x]][index].push_back(pos);
        }
    }

    std::vector<std::uint64_t> result;
    for (auto& byDirection : boundaryCells)
    {
        using namespace position;

        auto onLineY = [](const auto& left, const auto& right)
        {
            return (left.x + 1) == right.x && left.y == right.y;
        };
        auto onLineX = [](const auto& left, const auto& right)
        {
            return (left.y + 1) == right.y && left.x == right.x;
        };
        auto accumulate = [](const auto& range, auto group)
        {
            auto one = util::functional::constant(std::uint64_t{1});
            return ::ranges::accumulate(range | views::chunk_by(group), 0, std::plus{}, one);
        };
        byDirection[toIndex(DirectionIndex::Up)] |= actions::sort(lessByY);
        byDirection[toIndex(DirectionIndex::Down)] |= actions::sort(lessByY);
        byDirection[toIndex(DirectionIndex::Left)] |= actions::sort(lessByX);
        byDirection[toIndex(DirectionIndex::Right)] |= actions::sort(lessByX);

        result.push_back(
            accumulate(byDirection[toIndex(DirectionIndex::Up)], onLineY)
            + accumulate(byDirection[toIndex(DirectionIndex::Down)], onLineY)
            + accumulate(byDirection[toIndex(DirectionIndex::Right)], onLineX)
            + accumulate(byDirection[toIndex(DirectionIndex::Left)], onLineX));
    }
    return result;
}

namespace part1
{

std::uint64_t solve(const Map& input)
{
    using namespace ::ranges;
    auto fill = [&]
    {
        Filler fill{input};
        for (const auto& pos : position::all(std::ssize(input), std::ssize(input[0])))
            fill(pos);
        return fill;
    }();
    auto squares = computeSquares(fill);
    auto perimeters = computePerimeters(fill);
    return accumulate(  //
        views::zip(squares, perimeters)
            | views::transform(
                [](const auto& data)
                {
                    return std::get<0>(data) * std::get<1>(data);
                }),
        std::uint64_t{0});
}


void test()
{
    {
        Map map{
            "RRRRIICCFF",
            "RRRRIICCCF",
            "VVRRRCCFFF",
            "VVRCCCJFFF",
            "VVVVCJJCFE",
            "VVIVCCJJEE",
            "VVIIICJJEE",
            "MIIIIIJJEE",
            "MIIISIJEEE",
            "MMMISSJEEE",
        };
        auto solution = solve(map);
        fmt::print("Part I Test1: {}\n", solution);
        assert(solution == 1930);
    }
}

void solution()
{
    auto solution = solve(input());
    fmt::print("Part I: {}\n", solution);  // 1424472
    assert(solution == 1424472);
}
}  // namespace part1

namespace part2
{

std::uint64_t solve(const Map& input)
{
    using namespace ::ranges;

    auto fill = [&]
    {
        Filler fill{input};
        for (const auto& pos : position::all(std::ssize(input), std::ssize(input[0])))
            fill(pos);
        return fill;
    }();

    auto squares = computeSquares(fill);
    auto edges = countEdges(fill);

    return accumulate(  //
        views::zip(squares, edges)
            | views::transform(
                [](const auto& data)
                {
                    return std::get<0>(data) * std::get<1>(data);
                }),
        std::uint64_t{0});
}


void test()
{
    {
        Map map{
            "RRRRIICCFF",
            "RRRRIICCCF",
            "VVRRRCCFFF",
            "VVRCCCJFFF",
            "VVVVCJJCFE",
            "VVIVCCJJEE",
            "VVIIICJJEE",
            "MIIIIIJJEE",
            "MIIISIJEEE",
            "MMMISSJEEE",
        };
        auto solution = solve(map);
        fmt::print("Part II Test1: {}\n", solution);
        assert(solution == 1206);
    }
}

void solution()
{
    auto solution = solve(input());
    fmt::print("Part II: {}\n", solution);  // 870202
    assert(solution == 870202);
}
}  // namespace part2
}  // namespace aoc2024::day12

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day12;
    part1::test();
    util::withTimer("part1::solution", part1::solution);
    part2::test();
    util::withTimer("part2::solution", part2::solution);
    return 0;
}