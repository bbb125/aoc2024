#include "util/functional.h"
#include "util/position.h"

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

        if (auto it = cache[depth].find(input); it != cache[depth].end())
            return it->second;

        auto result = accumulate(  //
            input | views::sliding(2)
                | views::transform(
                    [&](const auto& pair)
                    {
                        using namespace best_moves;
                        return self(arrowpad[arrowpadIndex(pair[0])][arrowpadIndex(pair[1])],
                                    depth - 1);
                    }),
            0ul);
        cache[depth].emplace(input, result);
        return result;
    };

    return solver(arrowPath, depth);
}

std::uint64_t solveCodeCached(std::string_view code, std::size_t depth)
{
    using namespace ::ranges;
    using namespace best_moves;

    using Cache = std::vector<std::vector<std::size_t>>;
    constexpr std::size_t arrowpadSize = 5;
    Cache cache{arrowpadSize, std::vector<std::size_t>(arrowpadSize, 1)};
    for (std::size_t i = 0; i < depth; ++i)
    {
        Cache nextCache{arrowpadSize, std::vector<std::size_t>(arrowpadSize, 1)};
        for (auto [j, k] : views::cartesian_product(views::iota(0u, arrowpadSize),
                                                    views::iota(0u, arrowpadSize)))
        {
            auto path = std::string{arrowpad[j][k]};
            if (path.length() <= 1)
                continue;

            nextCache[j][k] = accumulate(  //
                path | views::sliding(2)
                    | views::transform(
                        [&](const auto& pair)
                        {
                            return cache[arrowpadIndex(pair[0])][arrowpadIndex(pair[1])];
                        }),
                0ul,
                std::plus{});
        }
        cache = std::move(nextCache);
        fmt::print("Cache: \n{}\n", fmt::join(cache, "\n"));
    }

    fmt::print("{}\n", code);
    auto target = "A" + arrowpadPath(code);

    auto result = accumulate(  //
        target | views::sliding(2)
            | views::transform(
                [&cache](const auto& pair)
                {
                    return cache[arrowpadIndex(pair[0])][arrowpadIndex(pair[1])];
                }),
        0ul,
        std::plus{});
    fmt::print("\nResult: {}\n", result);
    return result;
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

    // test: "029A", "980A", "179A", "456A", "379A"
    {
        auto result = accumulate(  //
            std::to_array<std::string_view>({"029A", "980A", "179A", "456A", "379A"}),
            0ul,
            std::plus{},
            [](const auto& code)
            {
                return solveCodeRecursive(code, 2) * codeNumber(code);
            });
        assert(result = 126384);
        fmt::print("Part I: {}\n", result);
    }
    {
        auto result = accumulate(  //
            std::to_array<std::string_view>({"029A", "980A", "179A", "456A", "379A"}),
            0ul,
            std::plus{},
            [](const auto& code)
            {
                return solveCodeRecursive(code, 25)
                       * codeNumber(code);
            });
        assert(result = 154115708116294);
        fmt::print("Part II: {}\n", result);
    }
    return 0;
}