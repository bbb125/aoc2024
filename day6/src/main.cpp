#include "inputs.h"

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
struct Position
{
    constexpr bool operator==(const Position& other) const = default;

    int x = 0;
    int y = 0;
};

struct Direction
{
    int x = 0;
    int y = 0;
};

Position move(Position position, Direction direction)
{
    return {position.x + direction.x, position.y + direction.y};
}

// directions ordered clockwise
enum class DirectionIndex
{
    Up,
    Right,
    Down,
    Left,
};

constexpr inline Direction up{0, -1};
constexpr inline Direction down{0, 1};
constexpr inline Direction left{-1, 0};
constexpr inline Direction right{1, 0};

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
        h = h * 31 + std::hash<int>{}(guard.position.x);
        h = h * 31 + std::hash<int>{}(guard.position.y);
        h = h * 31 + std::hash<int>{}(std::to_underlying(guard.direction));
        return h;
    }
};
}  // namespace std
namespace aoc2024::day6
{
using MapData = std::vector<std::string>;

struct Map
{
    Map(MapData map)
        : data{std::move(map)}
    {}

    bool isWall(const Position& position)
    {
        return data[position.y][position.x] == '#';
    }

    bool hasLoop(const Guard& guard) const { return visited.contains(guard); }

    bool end(const Position& position)
    {
        return position.x < 0 || position.y < 0 || position.x >= std::ssize(data[0])
               || position.y >= std::ssize(data);
    }

    void markAsVisited(const Guard& guard)
    {
        data[guard.position.y][guard.position.x] = 'X';
        visited.insert(guard);
    }

    bool wasPositionSeen(const Position& position) const
    {
        return data[position.y][position.x] == 'X';
    }

    void putObstacle(const Position& position)
    {
        data[position.y][position.x] = '#';
    }

    Guard findGuard() const
    {
        Guard guard;
        for (int y = 0; y < std::ssize(data); ++y)
        {
            for (int x = 0; x < std::ssize(data[0]); ++x)
            {
                Position position{x, y};
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
    std::unordered_set<Guard> visited;
};

enum class State
{
    Move,
    Loop,
    End,
};
State move(Map& map, Guard& guard)
{
    auto nextPosition = guard.nextPosition();
    if (map.end(nextPosition))
        return State::End;
    if (map.isWall(nextPosition))
    {
        guard.turn();
        return State::Move;
    }

    // move
    guard.position = nextPosition;
    if (map.hasLoop(guard))
        return State::Loop;

    map.markAsVisited(guard);
    return State::Move;
}

Guard initialize(Map& map)
{
    Guard guard = map.findGuard();
    map.markAsVisited(guard);
    return guard;
}

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
    Guard guard = initialize(map);
    while (move(map, guard) == State::Move)
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
State solve(Map map, Guard guard)
{
    State state = State::Move;
    while (state == State::Move)
        state = move(map, guard);
    return state;
}

int solve(Map map)
{
    Guard guard = initialize(map);
    int loops = 0;
    State state = State::Move;
    while (state == State::Move)
    {
        Map mapCopy = map;
        Guard guardCopy = guard;

        state = move(map, guard);
        if (!mapCopy.wasPositionSeen(guard.position) && state == State::Move)
        {
            mapCopy.putObstacle(guard.position);
            loops += solve(mapCopy, guardCopy) == State::Loop;
        }
    }
    return loops;
}


void test()
{
    std::print("Test Part II: {}\n", solve(testInputs()));
    assert(solve(testInputs()) == 6);
}

void solve()
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
    part2::solve();
    return 0;
}