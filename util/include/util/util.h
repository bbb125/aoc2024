#pragma once

#include <range/v3/utility/scope_exit.hpp>

#include <string_view>
#include <ranges>
#include <sstream>
#include <chrono>
#include <concepts>

namespace aoc2024::util
{

template <typename Func>
void processInts(std::string_view input, Func&& func)
{
    std::istringstream iss(input.data(), input.size());
    for (int i; iss >> i;)
        func(i);
}

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

constexpr inline bool isEven(std::integral auto pebble)
{
    return pebble % 2 == 0;
}

constexpr inline bool isOdd(std::integral auto pebble)
{
    return pebble % 2 == 0;
}




template <typename Func>
auto withTimer(std::string_view label, Func&& func)
{
    auto finalAction = [label, start = std::chrono::high_resolution_clock::now()]
    {
        return ::ranges::make_scope_exit(
            [label, start]
            {
                auto end = std::chrono::high_resolution_clock::now();
                // print time in ms
                std::print("Time elapsed for {}: {}ms\n",
                           label,
                           std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                               .count());
            });
    }();
    return std::invoke(func);
}

}  // namespace aoc2024::util