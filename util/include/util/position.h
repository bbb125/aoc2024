#pragma once

#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/iota.hpp>

#include <array>
#include <utility>
#include <functional>
#include <tuple>

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

auto format_as(const Position& position)
{
    return std::tie(position.y, position.x);
}

constexpr bool lessByX(const Position& lhs, const Position& rhs)
{
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

constexpr bool lessByY(const Position& lhs, const Position& rhs)
{
    return std::tie(lhs.y, lhs.x) < std::tie(rhs.y, rhs.x);
}

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
constexpr std::size_t toIndex(DirectionIndex index)
{
    return std::to_underlying(index);
}
using Direction = Delta;
constexpr inline Direction up{-1, 0};
constexpr inline Direction down{1, 0};
constexpr inline Direction left{0, -1};
constexpr inline Direction right{0, 1};

constexpr inline auto directions = std::to_array({up, right, down, left});

auto neighbours(const Position& pos)
{
    return directions | ranges::views::transform(std::bind_front(std::plus{}, pos));
}

auto all(std::size_t height, std::size_t width)
{
    using namespace ::ranges;
    return views::cartesian_product(views::iota(0, static_cast<int>(height)),
                                    views::iota(0, static_cast<int>(width)))
           | views::transform(
               [](const auto& val) -> Position
               {
                   return {std::get<0>(val), std::get<1>(val)};
               });
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