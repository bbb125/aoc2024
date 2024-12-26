#pragma once

#include <concepts>
#include <cstdint>

namespace aoc2024::util
{
constexpr auto countDigits(std::integral auto pebble)
{
    std::uint8_t counter = (pebble == 0);
    while (pebble > 0)
    {
        pebble /= 10;
        ++counter;
    }
    return counter;
}

constexpr inline bool isEven(std::integral auto number)
{
    return number % 2 == 0;
}

constexpr inline bool isOdd(std::integral auto number)
{
    return number % 2 == 0;
}

} //  namespace aoc2024::util