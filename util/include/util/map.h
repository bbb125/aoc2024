#pragma once

#include "position.h"

#include <string>
#include <vector>

namespace aoc2024::util::position
{
using MapData = std::vector<std::string>;

/**
 * A simple map wrapper.
 */
struct Map
{
    Map() = default;
    Map(MapData map)
        : data{std::move(map)}
    {}

    auto value(const Position& position) const
    {
        return data[position.y][position.x];
    }

    auto& value(const Position& position)
    {
        return data[position.y][position.x];
    }

    bool inBounds(const Position& position) const
    {
        return position.y >= 0 && position.y < std::ssize(data)
               && position.x >= 0 && position.x < std::ssize(data[0]);
    }

    auto all() const
    {
        return position::all(std::ssize(data), std::ssize(data[0]));
    }

    auto height() const
    {
        return static_cast<int>(std::ssize(data));
    }
    auto width() const
    {
        return static_cast<int>(std::ssize(data[0]));
    }

    auto dim() const
    {
        return std::tuple{height(), width()};
    }


    MapData data;
};

}  // namespace aoc2024::util::position