#pragma once

#include <range/v3/utility/scope_exit.hpp>

#include <string_view>
#include <ranges>
#include <sstream>
#include <chrono>

namespace aoc2024::util
{
template <typename Func>
void processInts(std::string_view input, Func&& func)
{
    std::istringstream iss(input.data(), input.size());
    for (int i; iss >> i;)
        func(i);
}

template <typename Func>
void withTimer(std::string_view label, Func&& func)
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
    std::invoke(func);
}

}  // namespace aoc2024::util