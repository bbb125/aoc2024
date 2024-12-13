#pragma once

#include <utility>
#include <type_traits>

namespace aoc2024::util::functional
{
inline constexpr auto constant = []<typename T>(T&& value)
{
    return [value = std::forward<T>(value)](auto&&...) -> decltype(auto)
    {
        using Type = std::remove_cvref_t<T>;

        if constexpr (std::is_fundamental_v<Type> || std::is_pointer_v<Type>
                      || std::is_enum_v<Type>)
        {
            return value;
        }
        else
            return (value);  // braces allow compiler to deduce return type as reference
    };
};

}  // namespace aoc2024::util::functional