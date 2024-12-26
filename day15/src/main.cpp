#include "input.h"
#include "util/map.h"
#include "util/position.h"

#include <range/v3/all.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cassert>
#include <vector>
#include <string_view>
#include <unordered_set>
#include <list>

namespace aoc2024::day15
{
namespace position = aoc2024::util::position;


auto value(const position::MapData& data, const position::Position& pos)
{
    return data[pos.y][pos.x];
}
auto& value(position::MapData& data, const position::Position& pos)
{
    return data[pos.y][pos.x];
}

Input smallTest()
{
    return {
        .data =
            position::MapData{
                "########",
                "#..O.O.#",
                "##@.O..#",
                "#...O..#",
                "#.#.O..#",
                "#...O..#",
                "#......#",
                "########",
            },
        .moves = "<^^>>>vv<v>>v<<",
    };
}


Input testInput()
{
    return {
        .data =
            position::MapData{
                "##########",
                "#..O..O.O#",
                "#......O.#",
                "#.OO..O.O#",
                "#..O@..O.#",
                "#O#..O...#",
                "#O..O..O.#",
                "#.OO.O.OO#",
                "#....O...#",
                "##########",  //
            },
        .moves =  // clang-format off
"<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^"
"vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v"
"><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<"
"<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^"
"^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><"
"^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^"
">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^"
"<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>"
"^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>"
"v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^"
                  // clang-format on
    };
}

std::uint64_t posToValue(const position::Position& pos)
{
    return 100 * pos.y + pos.x;
}

namespace part1
{

struct WorldState
{
    bool moveRobot()
    {
        auto direction = moves[currentStep++];
        auto next = robot + direction;

        auto boxPos = next;
        while (map.inBounds(boxPos) && boxes.contains(boxPos) && map.value(boxPos) != '#')
            boxPos += direction;

        if (map.inBounds(boxPos) && map.value(boxPos) != '#' && next != boxPos)
        {
            boxes.erase(next);
            boxes.insert(boxPos);
        }

        if (map.inBounds(next) && map.value(next) != '#' && !boxes.contains(next))
            robot = next;
        return currentStep < moves.size();
    }

    position::Position robot{};
    std::unordered_set<position::Position> boxes{};
    position::Map map;
    std::vector<position::Direction> moves;
    std::size_t currentStep = 0;
};

std::uint64_t solve(WorldState state)
{
    using namespace ::ranges;
    while (state.moveRobot())
        ;

    return accumulate(state.boxes, std::uint64_t{0}, std::plus{}, posToValue);
}

WorldState initialize(Input input)
{
    using namespace ::ranges;
    WorldState result{.map = position::Map{std::move(input.data)}};
    for (const auto& pos : result.map.all())
    {
        auto& val = result.map.value(pos);
        if (val == '@')
        {
            result.robot = pos;
            val = '.';
        }
        else if (result.map.value(pos) == 'O')
        {
            result.boxes.insert(pos);
            val = '.';
        }
    }

    for (auto [_, move] : input.moves | ranges::views::transform(position::fromChar))
        result.moves.push_back(move);
    return result;
}

void test()
{
    {
        auto solution = solve(initialize(smallTest()));
        fmt::print("Part I Test 1: {}\n", solution);
        assert(solution == 2028);
    }
    {
        auto solution = solve(initialize(testInput()));
        fmt::print("Part I Test 2: {}\n", solution);
        assert(solution == 10092);
    }
}

void solution()
{
    auto solution = solve(initialize(input()));
    fmt::print("Part I: {}\n", solution);
    assert(solution == 1527563);
}
}  // namespace part1

namespace part2
{
struct Box
{
    position::Position position;
    position::Direction next;
};

struct WorldState
{
    bool moveRobot()
    {
        auto [directionIndex, direction] = moves[currentStep++];
        auto next = robot + direction;

        if (!map.inBounds(next) || map.value(next) == '#')
            return currentStep < moves.size();

        if (map.value(next) == '.' && !boxes.contains(next))  // move robot
        {
            robot = next;
            return currentStep < moves.size();
        }

        auto [canMove, boxesToMove] = [&] -> std::pair<bool, std::vector<Box>>
        {
            if (directionIndex == position::DirectionIndex::Left
                || directionIndex == position::DirectionIndex::Right)
            {
                std::vector<Box> result;

                auto boxPos = next;
                while (map.inBounds(boxPos) && boxes.contains(boxPos))
                {
                    result.push_back(boxes[boxPos]);
                    boxPos += direction;
                }

                return map.inBounds(boxPos) && map.value(boxPos) != '#'
                           ? std::pair{true, std::move(result)}
                           : std::pair{false, std::vector<Box>{}};
            }
            else  // up or down
            {
                std::vector<Box> result;
                std::list<position::Position> toProcess{next};
                std::unordered_set<position::Position> visited;
                while (!std::empty(toProcess))
                {
                    auto pos = toProcess.front();
                    toProcess.pop_front();

                    if (visited.contains(pos))
                        continue;

                    if (!boxes.contains(pos))
                        continue;
                    auto& box = boxes[pos];

                    result.push_back(box);
                    visited.insert(pos);

                    // 2nd part of the box
                    toProcess.push_back(pos + box.next);

                    // move upper/bottom boxes
                    auto movePos = pos + direction;
                    if (!map.inBounds(movePos) || map.value(movePos) == '#')
                        return std::pair{false, std::vector<Box>{}};

                    if (boxes.contains(movePos))
                        toProcess.push_back(movePos);
                }
                return std::pair{true, std::move(result)};
            }
        }();

        if (canMove)
        {
            // move boxes
            std::vector<std::unordered_map<position::Position, Box>::node_type> extractedNodes;
            for (auto& box : boxesToMove)
                extractedNodes.push_back(boxes.extract(box.position));

            for (auto& node : extractedNodes)
            {
                node.key() += direction;
                node.mapped().position += direction;
                boxes.insert(std::move(node));
            }
            robot = next;
        }
        return currentStep < moves.size();
    }

    void debug()
    {
        auto mapData = map.data;
        for (const auto& [pos, box] : boxes)
            mapData[pos.y][pos.x] = box.next == position::left ? ']' : '[';
        mapData[robot.y][robot.x] = '@';
        fmt::print("Map {}: \n{}\n", currentStep, fmt::join(mapData, "\n"));
    }

    position::Position robot{};
    std::unordered_map<position::Position, Box> boxes;
    position::Map map;
    std::vector<position::DirectionDescription> moves;
    std::size_t currentStep = 0;
};

WorldState initialize(const Input& inp)
{
    using namespace ::ranges;
    position::MapData data{std::size(inp.data)};
    position::Position robot;
    std::unordered_map<position::Position, Box> boxes;
    std::vector<position::DirectionDescription> moves;
    for (const auto& [j, row] : inp.data | views::enumerate)
    {
        for (const auto& [i, val] : row | views::enumerate)
        {
            auto pos =
                position::Position{static_cast<int>(j), 2 * static_cast<int>(i)};

            char toWrite = [&]
            {
                if (val == 'O')
                {
                    boxes.insert({pos, Box{pos, position::right}});
                    auto other = pos + position::right;
                    boxes.insert({other, Box{other, position::left}});
                }
                if (val == '#')
                    return '#';
                else if (val == '@')
                    robot = pos;

                return '.';
            }();

            data[j].push_back(toWrite);
            data[j].push_back(toWrite);
        }
    }

    for (auto move : inp.moves | ranges::views::transform(position::fromChar))
        moves.push_back(move);
    return {.robot = robot,
            .boxes = std::move(boxes),
            .map = std::move(data),
            .moves = std::move(moves)};
}

std::uint64_t solve(WorldState world)
{
    using namespace ::ranges;
    while (world.moveRobot())
        ;

    return accumulate(world.boxes | views::values
                          | views::filter(std::bind_front(std::equal_to{}, position::right),
                                          &Box::next)
                          | views::transform(&Box::position),
                      std::uint64_t{0},
                      std::plus{},
                      posToValue);
}

void test()
{
    {
        auto solution = solve(initialize(testInput()));
        fmt::print("Part I Test 2: {}\n", solution);
    }
}

void solution()
{
    auto solution = solve(initialize(input()));
    fmt::print("Part I: {}\n", solution);
    assert(solution == 1521635);
}

}  // namespace part2
}  // namespace aoc2024::day15

int main()
{
    using namespace aoc2024;
    using namespace aoc2024::day15;
    part1::test();
    part1::solution();
    part2::test();
    part2::solution();


    return 0;
}