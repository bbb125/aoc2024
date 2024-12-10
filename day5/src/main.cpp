#include "inputs.h"

#include <cassert>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <print>
#include <span>

namespace aoc2024::day5
{
using OrderingRule = std::pair<int, int>;
using OrderingRules = std::vector<OrderingRule>;

using IndexedRules = std::unordered_set<OrderingRule>;
}  // namespace aoc2024::day5

namespace std
{
template <>
struct hash<aoc2024::day5::OrderingRule>
{
    std::size_t operator()(const aoc2024::day5::OrderingRule& rule) const
    {
        // very bad has implementation, which is ok for this task
        return std::hash<int>{}(rule.first) ^ std::hash<int>{}(rule.second);
    }
};
}  // namespace std

namespace aoc2024::day5
{
//

IndexedRules indexRules(const OrderingRules& rules)
{
    return {std::begin(rules), std::end(rules)};
}

/**
 * A much simpler alternative solution.
 * Just try to order based on passed rules and see whether the sequence is either
 * order (Part I) or not ordered (Part II).
 *
 * It works based on assumption that rules are comprehensive and there are no
 * contradictions.
 * Technically we could complete missing rules if it was necessary, but it's not.
 */

constexpr auto makeLess(const IndexedRules& rules)
{
    return [&rules](int a, int b)
    {
        return rules.contains({a, b});
    };
}

template <typename Pred>
int solveAll(const std::vector<std::vector<int>>& sequences,
             const IndexedRules& rules,
             Pred pred)
{
    return std::ranges::fold_left(  //
        sequences,
        0,
        [pred, &rules](int acc, const auto& seq)
        {
            std::vector<int> sorted(std::begin(seq), std::end(seq));
            std::ranges::stable_sort(sorted, makeLess(rules));

            return acc + (pred(seq, sorted) ? sorted[std::size(sorted) / 2] : 0);
        });
}

namespace part1
{
int predicate(std::span<const int> original, std::span<const int> sorted)
{
    return std::ranges::equal(original, sorted);
}


void test()
{
    std::vector<std::vector<int>> sequences{
        {75, 47, 61, 53, 29},
        {97, 61, 53, 29, 13},
        {75, 29, 13},
        {75, 97, 47, 61, 53},
        {61, 13, 29},
        {97, 13, 75, 29, 47}  //
    };
    OrderingRules rules{
        {47, 53}, {97, 13}, {97, 61}, {97, 47}, {75, 29}, {61, 13}, {75, 53},
        {29, 13}, {97, 29}, {53, 29}, {61, 53}, {97, 53}, {61, 29}, {47, 13},
        {75, 47}, {97, 75}, {47, 61}, {75, 61}, {47, 29}, {75, 13}, {53, 13},
    };
    assert(solveAll(sequences, indexRules(rules), predicate) == 143);
}

void solution()
{
    std::print("Alternative solution Part I: {}\n",
               solveAll(sequence(), indexRules(rules()), predicate));
}

}  // namespace part1

namespace part2
{
int predicate(std::span<const int> original, std::span<const int> sorted)
{
    return !std::ranges::equal(original, sorted);
}


void test()
{
    std::vector<std::vector<int>> sequences{
        {75, 47, 61, 53, 29},
        {97, 61, 53, 29, 13},
        {75, 29, 13},
        {75, 97, 47, 61, 53},
        {61, 13, 29},
        {97, 13, 75, 29, 47}  //
    };
    OrderingRules rules{
        {47, 53}, {97, 13}, {97, 61}, {97, 47}, {75, 29}, {61, 13}, {75, 53},
        {29, 13}, {97, 29}, {53, 29}, {61, 53}, {97, 53}, {61, 29}, {47, 13},
        {75, 47}, {97, 75}, {47, 61}, {75, 61}, {47, 29}, {75, 13}, {53, 13},
    };
    assert(solveAll(sequences, indexRules(rules), predicate) == 123);
}

void solution()
{
    std::print("Alternative solution Part II: {}\n",
               solveAll(sequence(), indexRules(rules()), predicate));
}

}  // namespace part2

}  // namespace aoc2024::day5

int main()
{
    using namespace aoc2024::day5;
    part1::test();
    part2::test();
    part1::solution();
    part2::solution();
}