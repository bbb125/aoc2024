#include "input.h"
#include "util/position.h"

#include <range/v3/all.hpp>

#include <cassert>
#include <vector>
#include <unordered_set>

namespace aoc2024::day8
{
using Position = util::position::Position;

Map testInput()
{
    return {
        "............",
        "........0...",
        ".....0......",
        ".......0....",
        "....0.......",
        "......A.....",
        "............",
        "............",
        "........A...",
        ".........A..",
        "............",
        "............",
    };
}

bool inBounds(const Map& map, const Position& position)
{
    return position.y >= 0 && position.y < std::ssize(map) && position.x >= 0
           && position.x < std::ssize(map[0]);
}

auto extractAntennas(const Map& map)
{
    using namespace ::ranges;
    std::unordered_map<char, std::vector<Position>> antennas;
    for (const auto& [y, row] : map | views::enumerate)
    {
        auto line = row | views::enumerate
                    | views::filter(
                        [](const auto& val)
                        {
                            return val.second != '.';
                        });
        for (const auto& [x, frequency] : line)
            antennas[frequency].emplace_back(y, x);
    }
    return antennas;
}

void print(Map map, const std::unordered_set<Position>& antinodes)
{
    for (const auto& pos : antinodes)
        map[pos.y][pos.x] = '#';
    for (const auto& row : map)
        std::print("{}\n", row);
}

namespace part1
{
int solve(const Map& map)
{
    using namespace ::ranges;
    auto antennas = extractAntennas(map);
    std::unordered_set<Position> antinodes;
    for (const auto& [frequency, positions] : antennas)
    {
        for (const auto& [i, pos1] : positions | views::enumerate)
        {
            for (const auto& pos2 : positions | views::drop(i + 1))
            {
                auto delta = pos1 - pos2;
                if (auto first = pos1 + delta; inBounds(map, first))
                    antinodes.insert(first);

                if (auto second = pos2 - delta; inBounds(map, second))
                    antinodes.insert(second);
            }
        }
    }
    return std::ssize(antinodes);
}

void test()
{
    std::print("{}\n", solve(testInput()));
    assert(solve(testInput()) == 14);
}

void solution()
{
    auto solution = solve(input());
    assert(solution == 327);
    std::print("{}\n", solution);
}
}  // namespace part1

namespace part2
{

int solve(const Map& map)
{
    using namespace ::ranges;
    auto antennas = extractAntennas(map);
    std::unordered_set<Position> antinodes;
    for (const auto& [frequency, positions] : antennas)
    {
        for (const auto& [i, pos1] : positions | views::enumerate)
        {
            for (const auto& pos2 : positions | views::drop(i + 1))
            {
                auto delta = pos1 - pos2;
                for (auto first = pos1; inBounds(map, first); first += delta)
                    antinodes.insert(first);

                for (auto second = pos2; inBounds(map, second); second -= delta)
                    antinodes.insert(second);
            }
        }
    }
    //        print(map, antinodes);
    return std::ssize(antinodes);
}

void test()
{
    std::print("{}\n", solve(testInput()));
    assert(solve(testInput()) == 34);
}

void solution()
{
    auto solution = solve(input());
    assert(solution == 1233);
    std::print("{}\n", solution);
}

}  // namespace part2
}  // namespace aoc2024::day8

int main()
{
    using namespace aoc2024::day8;
    part1::test();
    part1::solution();

    part2::test();
    part2::solution();
}