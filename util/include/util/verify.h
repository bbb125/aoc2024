#pragma once

#include <fmt/format.h>

#include <string_view>
#include <exception>
#include <source_location>

namespace aoc2024::util
{
constexpr void verify(std::string_view description,
                      bool condition,
                      std::source_location location = std::source_location::current())
{
    if (!condition)
    {
        fmt::print(stderr,
                   "Failure at: {}:{}:{}: {}\n",
                   location.file_name(),
                   location.line(),
                   location.column(),
                   description);
        std::terminate();
    }
}

}  // namespace aoc2024::util