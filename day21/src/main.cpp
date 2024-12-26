#include "util/functional.h"
#include "util/position.h"
#include "util/util.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <boost/unordered/unordered_flat_map.hpp>

#include <cassert>
#include <vector>
#include <unordered_set>
#include <deque>
#include <string>

namespace aoc2024::day21
{

namespace best_moves
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

}  // namespace best_moves

std::string arrowpadPath(std::string_view numpadCode)
{
    using namespace ::ranges;
    auto input = "A" + std::string{numpadCode};
    return accumulate(  //
        input | views::sliding(2)
            | views::transform(
                [](const auto& pair)
                {
                    using namespace best_moves;
                    return std::string(
                        numpad[numpadIndex(pair[0])][numpadIndex(pair[1])]);
                }),
        std::string{},
        std::plus{});
}

/**
 * Implements a recursive depth search approach with memoization.
 * @param code
 * @param depth
 * @return
 */
std::uint64_t solveCodeRecursive(std::string_view code, std::size_t depth)
{
    using namespace ::ranges;
    using namespace best_moves;

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
                        using namespace best_moves;
                        return self(arrowpad[pair[0]][pair[1]], depth - 1);
                    }),
            0ul);
        cache[depth].emplace(input, result);
        return result;
    };

    return solver(arrowPath, depth);
}


constexpr std::size_t arrowpadSize = best_moves::arrowpad.size();

using CacheLevel = std::array<std::array<std::size_t, arrowpadSize>, arrowpadSize>;

template <std::size_t Depth>
std::array<CacheLevel, Depth> buildCache()
{
    using namespace ::ranges;
    using namespace best_moves;
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

const auto precomputedCache = buildCache<26>();

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
std::uint64_t solveCodeCached(std::string_view code, std::size_t depth)
{
    using namespace ::ranges;
    using namespace best_moves;

    auto target = "A" + arrowpadPath(code);

    return accumulate(  //
        target | views::transform(arrowpadIndex) | views::sliding(2)
            | views::transform(
                [depth](const auto& pair)
                {
                    return precomputedCache[depth][pair[0]][pair[1]];
                }),
        0ul);
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

std::uint64_t solve(auto inputRange, std::size_t depth, auto solveFunction)
{
    using namespace ::ranges;
    return accumulate(  //
        inputRange,
        0ul,
        std::plus{},
        [&](const auto& code)
        {
            return solveFunction(code, depth) * codeNumber(code);
        });
}
}  // namespace aoc2024::day21

int main()
{
    using namespace aoc2024::day21;
    using namespace ::ranges;

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
    {
        auto result = solve(input, 2, solveCodeRecursive);
        assert(result = 126384);
        fmt::print("Part I: {}\n", result);
    }
    // test: "029A", "980A", "179A", "456A", "379A"
    {
        auto result = solve(input, 2, solveCodeCached);
        assert(result = 126384);
        fmt::print("Part I Another approach: {}\n", result);
    }
    {
        auto result = aoc2024::util::withTimer(  //
            "Solve Recursive:",
            [&]
            {
                return solve(input, 25, solveCodeRecursive);
            });
        assert(result = 154115708116294);
        fmt::print("Part II: {}\n", result);
    }
    {
        auto result = aoc2024::util::withTimer(  //
            "Solve With Precomputed Cache:",
            [&]
            {
                return solve(input, 25, solveCodeCached);
            });
        assert(result = 154115708116294);
        fmt::print("Part II Another approach: {}\n", result);
    }

    return 0;
}