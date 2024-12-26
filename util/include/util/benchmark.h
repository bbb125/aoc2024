#pragma once

#include <range/v3/utility/scope_exit.hpp>

#include <fmt/format.h>
#include <fmt/chrono.h>

#include <chrono>
#include <functional>
#include <string_view>

namespace aoc2024::util
{

template <typename Units = std::chrono::milliseconds>
auto withTimer(std::string_view label, auto&& func)
{
    auto finalAction = [label, start = std::chrono::high_resolution_clock::now()]
    {
        return ::ranges::make_scope_exit(
            [label, start]
            {
                auto end = std::chrono::high_resolution_clock::now();
                // print time in ms
                fmt::print("Time elapsed for {}: {}\n",
                           label,
                           std::chrono::duration_cast<Units>(end - start));
            });
    }();
    return std::invoke(std::forward<decltype(func)>(func));
}

}  // namespace aoc2024::util
