#include "util/util.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <boost/unordered/unordered_flat_map.hpp>

#include <vector>
#include <unordered_set>
#include <deque>
#include <string>
#include <functional>

namespace aoc2024::day21
{

// clang-format off
constexpr auto numpad = std::to_array({
    // From 0 to A
    std::to_array<std::string_view>(
        {"A", "^<A", "^A", ">^A", "^^<A", "^^A", ">^^A", "^^^<A", "^^^A", ">^^^A", ">A"}),
        {">vA", "A", ">A", ">>A", "^A", "^>A", "^>>A", "^^A", "^^>A", "^^>>A", ">>vA"},
        {"<vA", "<A", "A", ">A", "<^A", "^A", "^>A", "<^^A", "^^A", "^^>A", "v>A"},
        {"<vA", "<<A", "<A", "A", "<<^A", "<^A", "^A", "<<^^A", "<^^A", "^^A", "vA"},
        {">vvA", "vA", "v>A", "v>>A", "A", ">A", ">>A", "^A", "^>A", "^>>A", ">>vvA"},
        {"vvA", "<vA", "vA", "v>A", "<A", "A", ">A", "<^A", "^A", "^>A", "vv>A"},
        {"<vvA", "<<vA", "<vA", "vA", "<<A", "<A", "A", "<<^A", "<A", "^A", "vvA"},
        {">vvvA", "vvA", "vv>A", "vv>>A", "vA", "v>A", "v>>A", "A", ">A", ">>A", ">>vvvA"},
        {"vvvA", "<vvA", "vvA", "vv>A", "<vA", "vA", "v>A", "<A", "A", ">A", "vvv>A"},
        {"<vvvA", "<<vvA", "<vvA", "vvA", "<<vA", "<vA", "vA", "<<A", "<A", "A", "vvvA"},
        {"<A", "^<<A", "<^A", "^A", "^^<<A", "<^^A", "^^A", "^^^<<A", "<^^^A", "^^^A", "A"},  //
});  // clang-format on

constexpr auto arrowpad = std::to_array({
    // clang-format off
    std::to_array<std::string_view>(
        {"A", ">A", "v<A", "vA", "v>A"}),       // from ^ to ...
        {"<A", "A", "v<<A", "<vA", "vA"},       // from A to ...
        {">^A", ">>^A", "A", ">A", ">>A"},      // from < to ...
        {"^A", "^>A", "<A", "A", ">A"},         // from v to ...
        {"<^A", "^A", "<<A", "<A", "A"},        // from > to ...
});  // clang-format on

constexpr std::size_t numpadIndex(char ch)
{
    return ch == 'A' ? 10 : ch - '0';
}

constexpr std::size_t arrowpadIndex(char ch)
{
    switch (ch)
    {
    case '^':
        return 0;
    case 'A':
        return 1;
    case '<':
        return 2;
    case 'v':
        return 3;
    case '>':
        return 4;
    }
    std::unreachable();
}

std::string arrowpadPath(std::string_view numpadCode)
{
    using namespace ::ranges;
    auto input = "A" + std::string{numpadCode};
    return accumulate(  //
        input | views::transform(numpadIndex) | views::sliding(2)
            | views::transform(
                [](const auto& pair)
                {
                    return std::string(numpad[pair[0]][pair[1]]);
                }),
        std::string{});
}


std::uint64_t codeNumber(std::string_view code)
{
    using namespace ::ranges;
    return accumulate(  //
        code
            | views::filter(
                [](char ch)
                {
                    return std::isdigit(static_cast<unsigned char>(ch));
                }),
        0ul,
        [](auto acc, auto ch)
        {
            return acc * 10 + (ch - '0');
        });
}

auto solve = [](auto inputRange, std::size_t depth, auto solveFunction)
{
    using namespace ::ranges;
    return accumulate(  //
        inputRange,
        0ul,
        std::plus{},
        [&](const auto& code)
        {
            return std::invoke(solveFunction, code, depth) * codeNumber(code);
        });
};

namespace memoization_approach
{
/**
 * Implements a recursive depth search approach with memoization.
 * @param code
 * @param depth
 * @return
 */
std::uint64_t solve(std::string_view code, std::size_t depth)
{
    using namespace ::ranges;

    using LevelCache = boost::unordered_flat_map<std::string, std::uint64_t>;
    using Cache = std::vector<LevelCache>;

    Cache cache(depth + 1);

    auto arrowPath = arrowpadPath(code);

    auto solver = [&cache](this auto&& self,
                           std::string_view code,
                           std::size_t depth) -> std::uint64_t
    {
        if (depth == 0)
            return code.length();

        auto input = "A" + std::string{code};

        if (auto it = cache[depth].find(input); it != std::end(cache[depth]))
            return it->second;

        auto result = accumulate(  //
            input | views::transform(arrowpadIndex) | views::sliding(2)
                | views::transform(
                    [&](const auto& pair)
                    {
                        return self(arrowpad[pair[0]][pair[1]], depth - 1);
                    }),
            0ul);
        cache[depth].emplace(input, result);
        return result;
    };

    return solver(arrowPath, depth);
}

}  // namespace memoization_approach

namespace dynamic_programming_approach
{
constexpr std::size_t arrowpadSize = arrowpad.size();

using CacheLevel = std::array<std::array<std::size_t, arrowpadSize>, arrowpadSize>;

template <std::size_t Depth>
std::array<CacheLevel, Depth> buildCache()
{
    using namespace ::ranges;
    std::array<CacheLevel, Depth> cache{};
    for (auto i : views::iota(0u, arrowpadSize))
        cache[0][i].fill(1);

    for (std::size_t i = 1; i < Depth; ++i)
    {
        auto& prevCache = cache[i - 1];
        auto& currentCache = cache[i];
        for (auto [j, k] : views::cartesian_product(views::iota(0u, arrowpadSize),
                                                    views::iota(0u, arrowpadSize)))
        {
            auto path = "A" + std::string{arrowpad[j][k]};

            currentCache[j][k] = accumulate(  //
                path | views::transform(arrowpadIndex) | views::sliding(2)
                    | views::transform(
                        [&](const auto& pair)
                        {
                            auto [from, to] = std::tuple(pair[0], pair[1]);
                            return prevCache[from][to];
                        }),
                0ul);
        }
    }
    return cache;
}

const auto precomputedCache =
    aoc2024::util::withTimer<std::chrono::nanoseconds>("Cache initialization",
                                                       buildCache<26>);

/**
 * Implements a more dynamic programming approach, computing all lengths of
 * paths from deeper level to the top.
 * Technically this approach is better, because it can be precomputed (must be
 * even possible to implement it as a constexpr/consteval function).
 * Then reused for different inputs.
 * @param code
 * @param depth
 * @return
 */
std::uint64_t solve(std::string_view code, std::size_t depth)
{
    using namespace ::ranges;

    auto target = "A" + arrowpadPath(code);

    return accumulate(  //
        target | views::transform(arrowpadIndex) | views::sliding(2)
            | views::transform(
                [&cache = precomputedCache[depth]](const auto& pair)
                {
                    return cache[pair[0]][pair[1]];
                }),
        0ul);
}

}  // namespace dynamic_programming_approach
}  // namespace aoc2024::day21

int main()
{
    using namespace aoc2024::day21;

    /**
     *     +---+---+
     *     | ^ | A |
     * +---+---+---+
     * | < | v | > |
     * +---+---+---+
     *
     * +---+---+---+
     * | 7 | 8 | 9 |
     * +---+---+---+
     * | 4 | 5 | 6 |
     * +---+---+---+
     * | 1 | 2 | 3 |
     * +---+---+---+
     *     | 0 | A |
     *     +---+---+
     */

    auto input =
        std::to_array<std::string_view>({"029A", "980A", "179A", "456A", "379A"});

    auto verify = [&input](std::string_view description,
                           auto&& approach,
                           std::size_t depth,
                           std::uint64_t expected)
    {
        auto result = aoc2024::util::withTimer<std::chrono::nanoseconds>(  //
            description,
            std::bind_front(solve, input, depth, std::forward<decltype(approach)>(approach)));
        solve(input, 2, memoization_approach::solve);
        aoc2024::util::verify(description, result == expected);
        fmt::print("{}: {}\n", description, result);
    };

    verify("Part I Memoization Approach", memoization_approach::solve, 2, 126384);
    verify("Part I DP Approach", dynamic_programming_approach::solve, 2, 126384);
    verify("Part II Memoization Approach", memoization_approach::solve, 25, 154115708116294);
    verify("Part II DP Approach", dynamic_programming_approach::solve, 25, 154115708116294);

    return 0;
}