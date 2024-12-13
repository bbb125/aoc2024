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

struct Metrics
{
    char c = 0;  // useful for debug
    std::uint64_t square = 0;
    std::uint64_t perimeter = 0;
};

constexpr auto value(const Metrics& metrics)
{
    return metrics.square * metrics.perimeter;
}

constexpr auto format_as(const Metrics& metrics)
{
    return std::tie(metrics.c, metrics.square, metrics.perimeter);
}

struct Filler
{
    Filler(const Map& input)
        : map{input}
        , seen{std::size(input), std::vector<int>(std::ssize(input), unseen)}
    {}

    using Result = std::optional<Metrics>;
    Result operator()(const position::Position& pos)
    {
        if (seen[pos.y][pos.x] != unseen)
            return std::nullopt;

        //        return recursiveFill(pos, map[pos.y][pos.x], ++lastFiller);
        return fill(pos, lastFiller++);
    }

    Metrics recursiveFill(const position::Position& pos, char ch, int filler)
    {
        namespace rng = ::ranges;
        namespace rv = ::ranges::views;
        if (!inBounds(map, pos) || map[pos.y][pos.x] != ch)
            return Metrics{.c = ch, .square = 0, .perimeter = 1};

        if (visited(pos, filler))
            return Metrics{.c = ch, .square = 0, .perimeter = 0};
        markVisited(pos, filler);

        auto result = rng::accumulate(  //
            position::directions | rv::transform(std::bind_front(std::plus{}, pos)),
            Metrics{.c = map[pos.y][pos.x], .square = 1, .perimeter = 0},
            [this, ch, filler](Metrics metrics, const auto& currentPos)
            {
                auto neighbourMetrics = recursiveFill(currentPos, ch, filler);
                return Metrics{
                    .c = ch,
                    .square = neighbourMetrics.square + metrics.square,
                    .perimeter = neighbourMetrics.perimeter + metrics.perimeter  //
                };
            });
        return result;
    }

    Metrics fill(const position::Position& pos, int filler)
    {
        namespace rng = ::ranges;
        namespace rv = ::ranges::views;
        std::vector<position::Position> steps{pos};
        Metrics metrics{.c = map[pos.y][pos.x], .square = 1};
        markVisited(pos, filler);
        while (!std::empty(steps))
        {
            auto currentPos = steps.back();
            steps.pop_back();

            for (const auto& direction : position::directions)
            {
                auto neighbour = currentPos + direction;
                if (!inBounds(map, neighbour))
                {
                    metrics.perimeter += 1;
                    continue;
                }
                if (visited(neighbour, filler))
                    continue;

                if (map[neighbour.y][neighbour.x]
                    != map[currentPos.y][currentPos.x])
                    metrics.perimeter += 1;
                else
                {
                    markVisited(neighbour, filler);
                    metrics.square += 1;
                    steps.push_back(neighbour);
                }
            }
        }
        return metrics;
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
    int lastFiller = 0;
    std::vector<std::vector<int>> seen;
    static constexpr int unseen = -1;
};

namespace part1
{

std::uint64_t solve(const Map& input)
{
    using namespace ::ranges;
    return accumulate(  //
        position::all(std::ssize(input), std::ssize(input[0]))
            | views::transform(
                [fill = Filler{input}](const auto& pos) mutable -> Metrics
                {
                    return fill(pos).value_or(Metrics{});
                }),
        std::uint64_t{0},
        std::plus<>{},
        value);
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
    namespace rng = ::ranges;
    namespace rv = ::ranges::views;

    Filler fill{input};

    // ignore the result - will reuse previous solution, particularly feel
    std::vector<std::uint64_t> squares;
    for (const auto& pos : position::all(std::ssize(input), std::ssize(input[0])))
    {
        if (auto result = fill(pos))
            squares.push_back(result->square);
    }


    // select all boundary cells and their directions
    const auto& seen = fill.seen;

    using ByDirection = std::vector<position::Position>;
    std::vector<std::vector<ByDirection>> boundaryCells(  //
        fill.lastFiller + 1,
        std::vector<ByDirection>{position::directions.size()});

    for (const auto& pos : position::all(std::ssize(input), std::ssize(input[0])))
    {
        for (const auto& [index, direction] : position::directions | rv::enumerate)
        {
            auto neighbour = pos + direction;
            if (!inBounds(input, neighbour)
                || seen[pos.y][pos.x] != seen[neighbour.y][neighbour.x])
                boundaryCells[seen[pos.y][pos.x]][index].push_back(pos);
        }
    }

    std::uint64_t result = 0;
    for (const auto& [square, byDirection] : rv::zip(squares, boundaryCells))
    {
        using namespace position;
        byDirection[toIndex(DirectionIndex::Up)] |= rng::actions::sort(lessByY);
        byDirection[toIndex(DirectionIndex::Down)] |= rng::actions::sort(lessByY);
        byDirection[toIndex(DirectionIndex::Left)] |= rng::actions::sort(lessByX);
        byDirection[toIndex(DirectionIndex::Right)] |= rng::actions::sort(lessByX);

        auto onLineY = [](const auto& left, const auto& right)
        {
            return (left.x + 1) == right.x && left.y == right.y;
        };
        auto onLineX = [](const auto& left, const auto& right)
        {
            return (left.y + 1) == right.y && left.x == right.x;
        };
        auto one = util::functional::constant(std::uint64_t{1});
        auto res = rng::accumulate(  //
            byDirection[toIndex(DirectionIndex::Up)] | rv::chunk_by(onLineY),
            0,
            std::plus{},
            one);
        res += rng::accumulate(  //
            byDirection[toIndex(DirectionIndex::Down)] | rv::chunk_by(onLineY),
            0,
            std::plus{},
            one);
        res += rng::accumulate(
            byDirection[toIndex(DirectionIndex::Left)] | rv::chunk_by(onLineX),
            0,
            std::plus{},
            one);
        res += rng::accumulate(  //
            byDirection[toIndex(DirectionIndex::Right)] | rv::chunk_by(onLineX),
            0,
            std::plus{},
            one);
        result += res * square;
    }
    return result;
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