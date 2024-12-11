#include "input.h"

#include "util/util.h"

#include <range/v3/all.hpp>

#include <cassert>
#include <optional>
#include <string_view>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>

namespace aoc2024::day9
{
namespace part1
{
std::uint64_t solve(std::string_view input)
{
    using namespace ::ranges;
    using Block = std::optional<int>;
    std::vector<Block> filesystem;
    filesystem.reserve(10 * std::size(input));
    auto sizes = input | views::enumerate
                 | views::transform(
                     [](auto val)
                     {
                         return std::pair{val.second - '0',
                                          val.first % 2 == 0 ? Block{val.first / 2}
                                                             : std::nullopt};
                     });
    for (auto [blockSize, val] : sizes)
        filesystem.resize(filesystem.size() + blockSize, val);

    auto last = std::end(filesystem) - 1;
    auto first = std::begin(filesystem);
    for (; last != first;)
    {
        if (first->has_value())
            ++first;
        else if (!last->has_value())
            --last;
        else
            std::swap(*first, *last);
    }
    return accumulate(  //
        filesystem
            | views::take_while(
                [](const auto& val)
                {
                    return val.has_value();
                })
            | views::enumerate,
        std::uint64_t{0},
        [](auto acc, const auto& val)
        {
            return acc + val.first * val.second.value();
        });
}

void test()
{
    std::string_view input = "2333133121414131402";
    std::print("{}\n", solve(input));
    assert(solve(input) == 1928);
}

void solution()
{
    auto solution = solve(input);
    std::print("{}\n", solution);
    assert(solution = 6461289671426);
}
}  // namespace part1

namespace part2
{
struct Block
{
    bool empty() const { return !id.has_value(); }
    std::size_t size = 0;
    std::size_t offset = 0;
    std::optional<std::uint64_t> id;
};

std::uint64_t solve(std::string_view input)
{
    using namespace ::ranges;

    auto sizes = input  //
                 | views::enumerate
                 | views::transform(
                     [](auto val)
                     {
                         return std::pair{val.second - '0',
                                          val.first % 2 != 0
                                              ? std::nullopt
                                              : std::optional{val.first / 2}};
                     });

    // after unsuccessful attempt to use std::map - screw it, brute force
    using Filessystem = std::list<Block>;
    Filessystem fs;
    for (std::size_t offset = 0; auto [blockSize, id] : sizes)
    {
        if (blockSize == 0)
            continue;
        fs.emplace_back(blockSize, offset, id);
        offset += blockSize;
    }

    // we don't preserve order, it doesn't impact the result
    for (auto& [fileSize, fileOffset, _] :
         fs | views::reverse | views::filter(std::not_fn(&Block::empty)))
    {
        auto emptyBlocks = fs | views::filter(&Block::empty)
                           | views::take_while(
                               [fileOffset](const auto& block)
                               {
                                   return block.offset < fileOffset;
                               });
        auto& [emptySize, emptyOffset, _2] =
            *find_if(emptyBlocks,
                     std::bind_front(std::greater_equal{}, fileSize),
                     &Block::size);

        if (emptyOffset > fileOffset)
            continue;

        // update file block
        fileOffset = emptyOffset;

        // update empty block
        emptySize -= fileSize;
        emptyOffset += fileSize;
    }

    return accumulate(  //
        fs | views::filter(std::not_fn(&Block::empty))
            | views::transform(
                [](const auto& block)
                {
                    const auto& [size, offset, id] = block;
                    return *id * size * offset + (*id * size * (size - 1)) / 2;
                }),
        std::uint64_t{0},
        std::plus{});
}


void test()
{
    {
        std::string_view input = "2333133121414131402";
        std::print("Part II Test1: {}\n", solve(input));
        assert(solve(input) == 2858);
    }

    {
        std::string_view input2 = "12345";
        auto solution = solve(input2);
        std::print("Part II Test2: {}\n", solution);
        assert(solution == 132);
    }

    {
        auto solution = solve(testInput3);
        std::print("Part II Test3: {}\n", solution);
        assert(solution == 97898222299196);
    }
}

void solution()
{
    auto solution = solve(input);
    std::print("{}\n", solution);
    assert(solution = 6488291456470);
}
}  // namespace part2
}  // namespace aoc2024::day9

int main()
{
    using namespace aoc2024::day9;
    part1::test();
    part1::solution();

    aoc2024::util::withTimer("part2::test", part2::test);
    aoc2024::util::withTimer("part2::solution", part2::solution);
    return 0;
}