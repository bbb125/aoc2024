#include "util/util.h"

#include <range/v3/all.hpp>
#include <fmt/format.h>

#include <cstdlib>
#include <span>
#include <vector>
#include <unordered_map>

namespace aoc2024::day11
{

auto countDigits(std::uint64_t pebble)
{
    std::uint8_t counter = 0;
    while (pebble > 0)
    {
        pebble /= 10;
        ++counter;
    }
    return counter;
}

struct DigitsCounter
{
    std::unordered_map<std::uint64_t, std::uint8_t> digitsCache;
    std::uint8_t operator()(std::uint64_t pebble)
    {
        auto& digits = digitsCache[pebble];
        if (digits == 0)
            digits = countDigits(pebble);
        return digits;
    }
};

bool isEven(std::uint64_t pebble)
{
    return pebble % 2 == 0;
}

std::uint64_t evolvePebbles(std::span<std::uint64_t> input, std::uint64_t times)
{
    using namespace ::ranges;
    using PebbleGeneration = std::unordered_map<std::uint64_t, std::uint64_t>;
    PebbleGeneration currentGeneration = [&]
    {
        PebbleGeneration result;
        for (auto pebble : input)
            ++result[pebble];
        return result;
    }();
    DigitsCounter digitsCounter;
    for (std::size_t i = 0; i < times; ++i)
    {
        PebbleGeneration nextGeneration;
        for (const auto& [number, count] : currentGeneration)
        {
            if (number == 0)
                nextGeneration[1] += count;
            else if (auto digits = digitsCounter(number); isEven(digits))
            {
                std::uint64_t split = std::pow(10, digits / 2);
                nextGeneration[number / split] += count;
                nextGeneration[number % split] += count;
            }
            else
                nextGeneration[number * 2024] += count;
        }
        currentGeneration = std::move(nextGeneration);
    }
    return accumulate(currentGeneration,
                      std::uint64_t{0},
                      std::plus{},
                      &PebbleGeneration::value_type::second);
}
namespace part1
{


void test()
{
    {
        std::vector<std::uint64_t> input = {125, 17};
        auto solution = evolvePebbles(input, 25);
        fmt::print("Part I Test1: {}\n", solution);
    }
}

void solve()
{
    std::vector<std::uint64_t> input{64554, 35, 906, 6, 6960985, 5755, 975820, 0};
    auto solution = evolvePebbles(input, 25);
    fmt::print("Part I Solution: {}\n", solution);  // 175006
}
}  // namespace part1
namespace part2
{
void solve()
{
    std::vector<std::uint64_t> input{64554, 35, 906, 6, 6960985, 5755, 975820, 0};
    auto solution = evolvePebbles(input, 75);
    fmt::print("Part II Solution: {}\n", solution);  // 207961583799296 - 13ms
}
}  // namespace part2
}  // namespace aoc2024::day11

int main()
{
    using namespace aoc2024::day11;
    part1::test();
    aoc2024::util::withTimer("part1::solve", part1::solve);
    aoc2024::util::withTimer("part2::solve", part2::solve);
    return 0;
}