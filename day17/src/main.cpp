#include "util/functional.h"

#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <array>
#include <span>
#include <vector>

namespace aoc2024::day17
{
struct Vm
{
    using RegisterType = std::int64_t;

    Vm(RegisterType a)
        : state{.a = a, .b = 0, .c = 0, .ip = 0}
    {}

    struct State
    {
        auto registers() const { return std::span<const RegisterType>{&a, 3}; }


        std::string debug() const
        {
            return fmt::format(  //
                "a: {a:} ({a:b}), b: {b} ({b:b}), c: {c} ({c:b}), ip: {ip}",
                fmt::arg("a", a),
                fmt::arg("b", b),
                fmt::arg("c", c),
                fmt::arg("ip", ip));
        }

        RegisterType a = 0;
        RegisterType b = 0;
        RegisterType c = 0;
        int ip = 0;
        std::vector<int> out{};
    };

    /**
     * The value of a combo operand can be found as follows:
     *
     * Combo operands 0 through 3 represent literal values 0 through 3.
     * Combo operand 4 represents the value of register A.
     * Combo operand 5 represents the value of register B.
     * Combo operand 6 represents the value of register C.
     * Combo operand 7 is reserved and will not appear in valid programs.
     */
    constexpr RegisterType comboOperand(int value) const
    {
        if (value <= 3)
            return value;
        if (value <= 6)
            return state.registers()[value - 4];
        if (value == 7)
            throw std::invalid_argument{"Invalid combo operand"};
        std::unreachable();
    }
    constexpr RegisterType literalOperant(int value) const { return value; }

    enum class OpCode
    {
        adv,  // division, result into A register
        bxl,  // xor
        bst,  // modulo 8 and write to register
        jnz,  // jump not zero
        bxc,  // bitwise xor
        out,  // modulo 8 and write to output
        bdv,  // same as adv, but writes result into B register
        cdv,  // same as adv, but writes result into C register
    };


    constexpr void adv(int operand)
    {
        // The adv instruction (opcode 0) performs division. The numerator is the value
        // in the A register. The denominator is found by raising 2 to the power of
        // the instruction's combo operand. (So, an operand of 2 would divide A by 4
        // (2^2); an operand of 5 would divide A by 2^B.) The result of the division
        // operation is truncated to an integer and then written to the A register.
        state.a >>= comboOperand(operand);
    }

    constexpr void bxl(int operand)
    {
        // The bxl instruction (opcode 1) calculates the bitwise XOR of register B
        // and the instruction's literal operand, then stores the result in register B.
        state.b ^= literalOperant(operand);
    }

    constexpr void bst(int operand)
    {
        // The bst instruction (opcode 2) calculates the value of its combo
        // operand modulo 8 (thereby keeping only its lowest 3 bits), then
        // writes that value to the B register.
        state.b = comboOperand(operand) & (8 - 1);
    }

    constexpr void jnz(int operand)
    {
        // The jnz instruction (opcode 3) does nothing if the A register is 0.
        // However, if the A register is not zero, it jumps by setting the instruction
        // pointer to the value of its literal operand; if this instruction jumps,
        // the instruction pointer is not increased by 2 after this instruction.
        if (state.a != 0)
            state.ip = literalOperant(operand);
    }


    constexpr void bxc(int)
    {
        // The bxc instruction (opcode 4) calculates the bitwise XOR of register
        // B and register C, then stores the result in register B. (For legacy
        // reasons, this instruction reads an operand but ignores it.)
        state.b ^= state.c;
    }

    constexpr void out(int operand)
    {
        // The out instruction (opcode 5) calculates the value of its combo
        // operand modulo 8, then outputs that value. (If a program outputs
        // multiple values, they are separated by commas.)
        state.out.push_back(comboOperand(operand) & 7);
    }

    constexpr void bdv(int operand)
    {
        // The bdv instruction (opcode 6) works exactly like the adv instruction
        // except that the result is stored in the B register. (The numerator is
        // still read from the A register.)
        state.b = (state.a >> comboOperand(operand));
    }

    constexpr void cdv(int operand)
    {
        // The cdv instruction (opcode 7) works exactly like the adv instruction
        // except that the result is stored in the C register. (The numerator is
        // still read from the A register.)
        state.c = (state.a >> comboOperand(operand));
    }

    static constexpr auto ops = std::to_array(
        {&Vm::adv, &Vm::bxl, &Vm::bst, &Vm::jnz, &Vm::bxc, &Vm::out, &Vm::bdv, &Vm::cdv});

    using Program = std::span<const int>;

    std::span<const int> execute(const Program& program)
    {
        while (state.ip != std::ssize(program))
        {
            auto opcode = program[state.ip++];
            auto operand = program[state.ip++];
            std::invoke(ops[opcode], *this, operand);
        }
        return state.out;
    }

    // void reset()

    State state;
};


/*
 * {
 *    b <- a mod 8 (1000  1 10 11 100 101 110 111 1000)
 *    b <- b xor 1 (last bit 0)
 *    c <- a / 2**b
 *    b =  b xor 5 (101)
 *    a /= 8
 *    b = c
 *    out b
 * } while (register A is not zero)
 *
 * b = last 3 bits of a (a mod 8)
 * b = b xor 1 (meaning? flip the last bit)
 * c = a / b
 * b = b xor 5 (flip bit 3 and last bit)
 * a /= 8 (remove 3 bits from a)
 * b = b xor c
 * print last three bits of b
 * if a != 0 repeat
 *
 *
 */


namespace part1
{
void test()
{
    std::vector<int> program{0, 1, 5, 4, 3, 0};
    Vm vm{729};
    fmt::print("Part I Test: {}\n", fmt::join(vm.execute(program), ","));
}

void solution()
{
    std::vector<int> program{2, 4, 1, 1, 7, 5, 1, 5, 0, 3, 4, 3, 5, 5, 3, 0};
    Vm vm{56256477};
    fmt::print("Part I Solution: {}\n", fmt::join(vm.execute(program), ","));
}
}  // namespace part1
namespace part2
{

Vm::RegisterType search(std::span<const int> program)
{
    auto searcher =  //
        [&](this auto& self, Vm::RegisterType a, int pos) -> std::optional<Vm::RegisterType>
    {
        if (pos == 0)
            return a;

        for (Vm::RegisterType aVal = a * 8; aVal < (a * 8 + 8); ++aVal)
        {
            if (Vm vm{aVal}; vm.execute(program).front() == program[pos - 1])
            {
                if (auto result = self(aVal, pos - 1))
                    return result;
            }
        }
        return std::nullopt;
    };
    return *searcher(0, std::ssize(program));
}

void solution()
{
    std::vector<int> program{2, 4, 1, 1, 7, 5, 1, 5, 0, 3, 4, 3, 5, 5, 3, 0};

    fmt::print("Part II Solution: {}\n", search(program));

    // self-test
    Vm vm{164542125272765};
    auto out = vm.execute(program);
    fmt::print("Self-test {}", ::ranges::equal(program, out) ? "passed" : "failed");
}
}  // namespace part2
}  // namespace aoc2024::day17

int main()
{
    using namespace aoc2024::day17;
    part1::test();
    part1::solution();
    part2::solution();
    return 0;
}