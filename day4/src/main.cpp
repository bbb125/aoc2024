#include "input.h"

#include <range/v3/all.hpp>

#include <cassert>
#include <mdspan>
#include <vector>
#include <print>

namespace aoc2024::day4
{

// todo: replace with Position
struct Point
{
    int x = 0;
    int y = 0;
};

using Matrix = std::vector<std::string>;

bool inBounds(const Point& point, const Matrix& matrix)
{
    return point.x >= 0 && point.y >= 0 && point.x < std::ssize(matrix)
           && point.y < std::ssize(matrix[0]);
}

namespace part1
{
struct Direction
{
    int x = 0;
    int y = 0;
};

constexpr Direction right{1, 0};
constexpr Direction down{0, 1};
constexpr Direction left{-1, 0};
constexpr Direction up{0, -1};
constexpr Direction downRight{1, 1};
constexpr Direction downLeft{-1, 1};
constexpr Direction upRight{1, -1};
constexpr Direction upLeft{-1, -1};
constexpr auto directions =
    std::to_array({right, down, left, up, downRight, downLeft, upRight, upLeft});


Point operator+(const Point& lhs, const Direction& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

struct View
{
    const Matrix& data;
    Point start;
    int length;
    Direction direction;

    std::string asString() const
    {
        std::string result;
        result.reserve(length);
        Point p = start;
        for (int i = 0; inBounds(p, data) && i < length; ++i, p = p + direction)
            result.push_back(data[p.x][p.y]);
        return result;
    }
};

int countWords(const Matrix& m, std::string_view word)
{
    int count = 0;
    for (int i = 0; i < std::ssize(m); ++i)
    {
        for (int j = 0; j < std::ssize(m[i]); ++j)
        {
            for (const auto& direction : directions)
            {
                View view{.data = m,
                          .start = {i, j},
                          .length = static_cast<int>(std::ssize(word)),
                          .direction = direction};
                count += view.asString() == word;
            }
        }
    }
    return count;
}

void test()
{
    Matrix input{
        "MMMSXXMASM",
        "MSAMXMSMSA",
        "AMXSXMAAMM",
        "MSAMASMSMX",
        "XMASAMXAMM",
        "XXAMMXXAMA",
        "SMSMSASXSS",
        "SAXAMASAAA",
        "MAMMMXMMMM",
        "MXMXAXMASX"  //
    };
    std::print("{}\n", countWords(input, "XMAS"));
    assert(countWords(input, "XMAS") == 18);
}
}  // namespace part1

namespace part2
{
int countX(const Matrix& m)
{
    using namespace ::ranges;
    return accumulate(views::cartesian_product(views::iota(1, std::ssize(m) - 1),
                                               views::iota(1, std::ssize(m[0]) - 1)),
                      0,
                      [&](int acc, const auto& indices)
                      {
                          const auto [i, j] = indices;
                          return acc
                                 + (m[i][j] == 'A'
                                    && ((m[i - 1][j - 1] == 'M' && m[i + 1][j + 1] == 'S')
                                        || (m[i - 1][j - 1] == 'S' && m[i + 1][j + 1] == 'M'))
                                    && ((m[i - 1][j + 1] == 'M' && m[i + 1][j - 1] == 'S')
                                        || (m[i - 1][j + 1] == 'S'
                                            && m[i + 1][j - 1] == 'M')));
                      });
}

void test()
{
    Matrix m{
        ".M.S......",
        "..A..MSMS.",
        ".M.S.MAA..",
        "..A.ASMSM.",
        ".M.S.M....",
        "..........",
        "S.S.S.S.S.",
        ".A.A.A.A..",
        "M.M.M.M.M.",
        "..........",  //
    };
    std::print("{}\n", countX(m));
    assert(countX(m) == 9);
}
}  // namespace part2
}  // namespace aoc2024::day4

int main()
{
    using namespace aoc2024::day4;
    part1::test();
    std::print("Part 1: {}\n", part1::countWords(input(), "XMAS"));
    part2::test();
    std::print("Part 2: {}\n", part2::countX(input()));
    return 0;
}