#pragma once

#include "position.h"

#include <string>
#include <vector>

namespace aoc2024::util::position
{
using MapData = std::vector<std::string>;

struct Map
{
    Map(const MapData& map)
        : data{map}
    {}

    auto value(const Position& position) const
    {
        return data[position.y][position.x];
    }

    bool inBounds(const Position& position) const
    {
        return position.y >= 0 && position.y < std::ssize(data) && position.x >= 0
               && position.x < std::ssize(data[0]);
    }

    auto all() const
    {
        return position::all(std::ssize(data), std::ssize(data[0]));
    }

    const MapData& data;
};

}  // namespace aoc2024::util::position