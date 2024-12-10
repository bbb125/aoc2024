#pragma once

#include <array>
#include <utility>
#include <functional>

namespace aoc2024::util::position
{
using Delta = std::pair<int, int>;

struct Position
{
    constexpr bool operator==(const Position& other) const = default;
    constexpr bool operator!=(const Position& other) const = default;

    constexpr Position& operator+=(const Delta& delta)
    {
        y += delta.first;
        x += delta.second;
        return *this;
    }
    constexpr Position& operator-=(const Delta& delta)
    {
        y -= delta.first;
        x -= delta.second;
        return *this;
    }

    int y = 0;
    int x = 0;
};

constexpr Position operator+(const Position& pos, const Delta& delta)
{
    return {pos.y + delta.first, pos.x + delta.second};
}

constexpr Position operator-(const Position& pos, const Delta& delta)
{
    return {pos.y - delta.first, pos.x - delta.second};
}

constexpr Delta operator-(const Position& pos1, const Position& pos2)
{
    return {pos1.y - pos2.y, pos1.x - pos2.x};
}

// directions ordered clockwise
enum class DirectionIndex
{
    Up,
    Right,
    Down,
    Left,
};
using Direction = Delta;
constexpr inline Direction up{0, -1};
constexpr inline Direction down{0, 1};
constexpr inline Direction left{-1, 0};
constexpr inline Direction right{1, 0};

constexpr inline auto directions = std::to_array({up, right, down, left});

}  // namespace aoc2024::util::position

namespace std
{
template <>
struct hash<aoc2024::util::position::Position>
{
    std::size_t operator()(const aoc2024::util::position::Position& position) const
    {
        std::size_t h = 17;
        h = h * 31 + std::hash<int>{}(position.y);
        h = h * 31 + std::hash<int>{}(position.x);
        return h;
    }
};
}  // namespace std