#include "inputs.h"
#include "util/util.h"
#include "util/position.h"

#include <array>
#include <cassert>
#include <utility>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <print>
#include <unordered_set>
#include <functional>

namespace aoc2024::day6
{
using Position = util::position::Position;
using Direction = util::position::Delta;

constexpr Position move(const Position& position, const Direction& direction)
{
    return position + direction;
}

// directions ordered clockwise
enum class DirectionIndex
{
    Up,
    Right,
    Down,
    Left,
};

constexpr inline Direction up{-1, 0};
constexpr inline Direction down{1, 0};
constexpr inline Direction left{0, -1};
constexpr inline Direction right{0, 1};

constexpr inline auto directions = std::to_array({up, right, down, left});

constexpr DirectionIndex turn(DirectionIndex direction)
{
    auto index = std::to_underlying(direction);
    return static_cast<DirectionIndex>((index + 1) % std::ssize(directions));
}

constexpr const Direction& fromIndex(DirectionIndex index)
{
    return directions[std::to_underlying(index)];
}

struct Guard
{
    Position position;
    DirectionIndex direction;

    constexpr bool operator==(const Guard& other) const = default;
    auto nextPosition() const { return move(position, fromIndex(direction)); }
    void turn() { direction = day6::turn(direction); }
};
}  // namespace aoc2024::day6

namespace std
{
template <>
struct hash<aoc2024::day6::Guard>
{
    std::size_t operator()(const aoc2024::day6::Guard& guard) const
    {
        std::size_t h = 17;
        h = h * 31 + std::hash<aoc2024::day6::Position>{}(guard.position);
        h = h * 31 + std::hash<int>{}(std::to_underlying(guard.direction));
        return h;
    }
};
}  // namespace std
namespace aoc2024::day6
{
using MapData = std::vector<std::string>;


enum class State
{
    Move,
    Loop,
    End,
};

struct Map
{
    Map(MapData map)
        : data{std::move(map)}
        , guard{findGuard()}
    {
        markAsVisited();
    }

    bool isWall(const Position& position)
    {
        return data[position.y][position.x] == '#';
    }

    bool hasLoop() const { return visited.contains(guard); }

    bool end(const Position& position)
    {
        return position.x < 0 || position.y < 0 || position.x >= std::ssize(data[0])
               || position.y >= std::ssize(data);
    }

    void markAsVisited()
    {
        data[guard.position.y][guard.position.x] = 'X';
        visited.emplace(guard);
    }

    bool wasPositionSeen(const Position& position) const
    {
        return data[position.y][position.x] == 'X';
    }

    void putObstacle(const Position& position)
    {
        data[position.y][position.x] = '#';
    }

    State moveGuard()
    {
        auto nextPosition = guard.nextPosition();
        while (!end(nextPosition) && isWall(nextPosition))
        {
            guard.turn();
            nextPosition = guard.position;
        }
        if (end(nextPosition))
            return State::End;

        // move
        guard.position = nextPosition;
        if (hasLoop())
            return State::Loop;

        markAsVisited();
        return State::Move;
    }

    Guard findGuard() const
    {
        for (int y = 0; y < std::ssize(data); ++y)
        {
            for (int x = 0; x < std::ssize(data[0]); ++x)
            {
                Position position{.y = y, .x = x};
                switch (data[y][x])
                {
                case '^':
                    return {position, DirectionIndex::Up};
                case 'v':
                    return {position, DirectionIndex::Down};
                case '<':
                    return {position, DirectionIndex::Left};
                case '>':
                    return {position, DirectionIndex::Right};
                }
            }
        }
        std::unreachable();
    }
    MapData data;
    Guard guard;
    std::unordered_set<Guard> visited;
};

int countVisited(const Map& map)
{
    return std::ranges::fold_left(  //
        map.data,
        0,
        [](int acc, const auto& row)
        {
            return acc + std::ranges::count(row, 'X');
        });
}

Map testInputs()
{
    return Map{MapData{
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#...",
    }};
}
namespace part1
{
int solve(Map map)
{
    while (map.moveGuard() == State::Move)
        ;
    return countVisited(map);
}

void test()
{
    std::print("Test: {}\n", solve(testInputs()));
    assert(solve(testInputs()) == 41);
}

void solution()
{
    std::print("{}\n", solve(Map{input()}));
}
}  // namespace part1
namespace part2
{
State simpleSolve(Map map)
{
    while (true)
    {
        if (auto state = map.moveGuard(); state != State::Move)
            return state;
    }
}

int solve(Map map)
{
    int loops = 0;
    while (true)
    {
        Map copy = map;
        if (map.moveGuard() != State::Move)
            break;

        auto position = map.guard.position;
        if (!copy.wasPositionSeen(position))
        {
            copy.putObstacle(position);
            loops += simpleSolve(std::move(copy)) == State::Loop;
        }
    }

    return loops;
}


void test()
{
    std::print("Test Part II: {}\n", solve(testInputs()));
    assert(solve(testInputs()) == 6);
}

void solution()
{
    std::print("Part II: {}\n", solve(Map{input()}));
}
}  // namespace part2
}  // namespace aoc2024::day6

int main()
{
    using namespace aoc2024::day6;
    part1::test();
    part1::solution();
    part2::test();
    aoc2024::util::withTimer("part2::solution", part2::solution);
    return 0;
}