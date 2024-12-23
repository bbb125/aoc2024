#include "util/util.h"
#include "util/functional.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <boost/hana/functional/placeholder.hpp>
#include <boost/dynamic_bitset.hpp>

#include <array>
#include <vector>
#include <concepts>
#include <type_traits>
#include <tuple>

namespace aoc2024::day22
{
constexpr auto prune(std::integral auto value)
{
    /**
     * To prune the secret number, calculate the value of the secret number
     * modulo 16777216. Then, the secret number becomes the result of that
     * operation. (If the secret number is 100000000 and you were to prune the
     * secret number, the secret number would become 16113920.)
     */
    return value & (16777216 - 1);
}

constexpr auto mix(std::integral auto secret, std::same_as<decltype(secret)> auto value)
{
    /**
     * To mix a value into the secret number, calculate the bitwise XOR of
     * the given value and the secret number.
     * Then, the secret number becomes the result of that operation.
     * (If the secret number is 42 and you were to mix 15 into the secret
     * number, the secret number would become 37.)
     */
    return secret ^ value;
}

constexpr auto makeRandomGenerator(std::integral auto secret)
{
    return [seed = secret]() mutable
    {
        /**
         * Calculate the result of multiplying the secret number by 64.
         * Then, mix this result into the secret number.
         * Finally, prune the secret number.
         *
         * Calculate the result of dividing the secret number by 32.
         * Round the result down to the nearest integer.
         * Then, mix this result into the secret number.
         * Finally, prune the secret number.
         *
         * Calculate the result of multiplying the secret number by 2048.
         * Then, mix this result into the secret number.
         * Finally, prune the secret number.
         */
        auto result = seed;
        seed = prune(mix(seed, seed << 6));
        seed = prune(mix(seed, seed >> 5));
        seed = prune(mix(seed, seed << 11));
        return result;
    };
}

using Number = std::int64_t;

namespace part1
{
std::uint64_t solve(std::span<const Number> input, std::size_t iterations)
{
    using namespace ::ranges;

    return accumulate(input,
                      0ull,
                      std::plus<>{},
                      [&](auto value)
                      {
                          auto generator = makeRandomGenerator(value);
                          for (std::size_t i = 0; i < iterations; ++i)
                              generator();
                          return generator();
                      });
}
}  // namespace part1
namespace part2
{
using Numbers = std::vector<Number>;
using PriceChangeSequence = std::tuple<Number, Number, Number, Number>;
constexpr int changeRange = 19;
constexpr int changeOffset = 9;
constexpr auto pows = std::to_array<std::size_t>(
    {changeRange * changeRange * changeRange, changeRange* changeRange, changeRange, 1});

constexpr std::size_t toNumber(const PriceChangeSequence& sequence)
{
    return [&sequence]<std::size_t... Index>(std::index_sequence<Index...>) -> std::size_t
    {
        return (((std::get<Index>(sequence) + changeOffset) * pows[Index]) + ...);
    }(std::make_index_sequence<4>{});
}

constexpr PriceChangeSequence fromNumber(std::size_t number)
{
    return [number]<std::size_t... Index>(std::index_sequence<Index...>) -> PriceChangeSequence
    {
        return {(static_cast<Number>(number / pows[Index]) % changeRange
                 - changeOffset)...};
    }(std::make_index_sequence<4>());
}
constexpr std::size_t priceChangesSize = toNumber({9, 9, 9, 9}) + 1;

Numbers generatePriceSequence(Number number, std::size_t count)
{
    using namespace ::ranges;
    return views::generate(makeRandomGenerator(number)) | views::take(count + 1)
           | views::transform(
               [](auto value)
               {
                   return value % 10;
               })
           | to_vector;
}

struct Signal
{
    Number price = 0;
    PriceChangeSequence sequence;
};

std::vector<Signal> generateSignals(std::span<const Number> prices)
{
    using namespace ::ranges;
    return views::zip(prices | views::sliding(2)
                          | views::transform(
                              [](const auto& priceRecord)
                              {
                                  return priceRecord[1] - priceRecord[0];
                              })                // price changes
                          | views::sliding(4),  // sequence of four changes
                      prices | views::drop(4))  // zip with price after sequence
           | views::transform(
               [](const auto& changeSequence) -> Signal
               {
                   return {
                       .price = changeSequence.second,
                       .sequence = {changeSequence.first[0],
                                    changeSequence.first[1],
                                    changeSequence.first[2],
                                    changeSequence.first[3]}  //
                   };
               })
           | ranges::to_vector;
}
std::size_t generatePriceChange(std::span<const Number> input, std::size_t sequenceLength)
{
    using namespace ::ranges;

    struct Counting
    {
        void addIfNotPresent(std::size_t traderId, std::size_t price)
        {
            bananasCount += (!included.test(traderId)) * price;
            included.set(traderId);
        }
        std::size_t bananasCount = 0;
        boost::dynamic_bitset<> included;
    };

    using Totals = std::vector<Counting>;
    Totals totals = [&]
    {
        Totals result;
        result.resize(priceChangesSize);
        for (auto& value : result)
            value.included.resize(input.size(), false);
        return result;
    }();

    for (const auto& [traderId, value] : input | views::enumerate)
    {
        auto signals = generateSignals(generatePriceSequence(value, sequenceLength));
        for (const auto& [price, sequence] : signals)
        {
            auto index = toNumber(sequence);
            totals[index].addIfNotPresent(traderId, price);
        }
    }
    return max(totals, {}, &Counting::bananasCount).bananasCount;
}

}  // namespace part2
}  // namespace aoc2024::day22

int main()
{
    using namespace aoc2024::day22;
    std::vector<Number> test1{1, 10, 100, 2024};
    fmt::print("Part1: {}\n", part1::solve(test1, 2000));
    std::vector<Number> test2{1, 2, 3, 2024};
    fmt::print("Part2 Test: {}\n", part2::generatePriceChange(test2, 2000));

    //    aoc2024::util::withTimer("Part2", part2::solve); 55ms
    return 0;
}