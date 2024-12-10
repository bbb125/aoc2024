#pragma once

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