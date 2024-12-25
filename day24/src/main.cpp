#include "util/util.h"
#include "util/functional.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/all.hpp>

#include <ctre.hpp>

#include <fstream>
#include <unordered_map>
#include <unordered_set>

/**
 * Tiny wrapper to generate graphviz dot file.
 * Because I'm not in a mood to solve Part II programmatically.
 */
namespace graphviz
{
struct Node
{
    std::string name;
    std::string label;
};

struct Subgraph
{
    std::unordered_set<std::string> nodes;
};

struct Digraph
{
    Digraph(std::string name)
        : name_{name}
    {}

    void addNode(Node node) { nodes_[node.name] = std::move(node); }
    void addNode(const std::string& subgraph, Node node)
    {
        subgraphs_[subgraph].nodes.insert(node.name);
        addNode(std::move(node));
    }

    void addEdge(std::string from, std::string to)
    {
        edges_.emplace(std::move(from), std::move(to));
    }

    std::string name_;
    std::unordered_map<std::string, Subgraph> subgraphs_;
    std::unordered_map<std::string, Node> nodes_;
    std::unordered_multimap<std::string, std::string> edges_;
};

void dump(std::ostream& out, const Node& node)
{
    out << fmt::format("{} [label=\"{}\"];\n", node.name, node.label);
}

void dump(std::ostream& out, const Digraph& digraph)
{
    out << fmt::format("digraph {} {{\n", digraph.name_);

    std::unordered_set<std::string> dumpedNodes;
    for (const auto& [name, subgraph] : digraph.subgraphs_)
    {
        out << fmt::format("  subgraph {} {{\n", name);
        for (const auto& node : subgraph.nodes)
        {
            dump(out, digraph.nodes_.at(node));
            dumpedNodes.insert(node);
        }
        out << "  }\n";
    }

    for (const auto& [name, node] : digraph.nodes_
                                        | ranges::views::filter(
                                            [&dumpedNodes](const auto& pair)
                                            {
                                                return !dumpedNodes.contains(pair.first);
                                            }))
    {
        out << fmt::format("  {} [label=\"{}\"];\n", name, node.label);
    }

    for (const auto& [from, to] : digraph.edges_)
        out << fmt::format("  {} -> {};\n", from, to);
    out << "}\n";
}

}  // namespace graphviz

namespace aoc2024::day24
{
struct Machine
{
    enum class Op
    {
        AND,
        OR,
        XOR,
    };

    struct Operation
    {
        std::string input1;
        std::string input2;
        std::string output;
        Op operation;
    };

    std::uint64_t getNumericValue(char latter) const
    {
        using namespace ::ranges;
        auto filtered = values
                        | views::filter(
                            [latter](const auto& pair)
                            {
                                return pair.first[0] == latter;
                            })
                        | views::transform(
                            [](const auto& pair)
                            {
                                return std::pair{pair.first, pair.second};
                            })
                        | to_vector;
        return accumulate(
            filtered |= actions::sort(std::greater{},
                                      &std::pair<std::string, std::uint64_t>::first),
            std::uint64_t{},
            [](std::uint64_t acc, const auto& value)
            {
                return (acc << 1) | value;
            },
            aoc2024::util::functional::selectIth<1>);
    };

    std::unordered_map<std::string, std::uint64_t> values;
    std::vector<Operation> operations;
};

Machine::Op fromString(std::string_view op)
{
    if (op == "AND")
        return Machine::Op::AND;
    if (op == "OR")
        return Machine::Op::OR;
    if (op == "XOR")
        return Machine::Op::XOR;
    std::unreachable();
}

Machine loadFromFile(std::string filename)
{
    Machine result;
    std::ifstream file(filename);

    using namespace ctre::literals;
    for (std::string line; std::getline(file, line);)
    {
        auto inputsExpression = "(?<input>[a-z]\\d+): (?<value>\\d)"_ctre;
        auto opsExpression =
            "(?<input1>\\w+)\\s+(?<operator>XOR|OR|AND)\\s+(?<input2>\\w+)?\\s*->\\s*(?<output>\\w+)"_ctre;
        if (auto [whole, input, value] = inputsExpression.match(line); whole)
        {
            result.values[input.to_string()] = value.to_number();
        }
        else if (auto [whole, input1, op, input2, output] = opsExpression.match(line); whole)
        {
            auto operation = fromString(op.to_view());
            result.operations.emplace_back(input1.to_string(),
                                           input2.to_string(),
                                           output.to_string(),
                                           operation);
        }
    }
    return result;
}

namespace part1
{
std::uint64_t solve(Machine machine)
{
    using namespace ::ranges;
    struct OperationData
    {
        Machine::Op operation;
        std::string output;
        std::optional<std::uint64_t> input1;
        std::optional<std::uint64_t> input2;

        bool ready() const { return input1.has_value() && input2.has_value(); }

        std::uint8_t evaluate() const
        {
            switch (operation)
            {
            case Machine::Op::AND:
                return input1.value() & input2.value();
            case Machine::Op::OR:
                return input1.value() | input2.value();
            case Machine::Op::XOR:
                return input1.value() ^ input2.value();
            }
            std::unreachable();
        }

        void set(std::uint64_t value)
        {
            if (!input1.has_value())
                input1 = value;
            else if (!input2.has_value())
                input2 = value;
        }
    };

    auto toProces = machine.values | views::keys | to<std::deque>;

    auto operations = machine.operations
                      | views::transform(
                          [](const auto& operation) -> OperationData
                          {
                              return {operation.operation, operation.output, {}, {}};
                          })
                      | to_vector;
    using ChildToParents =
        std::unordered_map<std::string_view, std::vector<std::reference_wrapper<OperationData>>>;

    ChildToParents childToParents;
    for (const auto& [opRelation, opData] : views::zip(machine.operations, operations))
    {
        childToParents[opRelation.input1].emplace_back(opData);
        childToParents[opRelation.input2].emplace_back(opData);
    }

    while (!std::empty(toProces))
    {
        auto value = toProces.front();
        toProces.pop_front();
        if (auto it = childToParents.find(value); it != std::end(childToParents))
        {
            for (const auto& opRef : it->second)
            {
                auto& operation = opRef.get();
                operation.set(machine.values[value]);
                if (operation.ready())
                {
                    machine.values[operation.output] = operation.evaluate();
                    toProces.push_back(operation.output);
                }
            }
        }
    }
    return machine.getNumericValue('z');
}
}  // namespace part1

namespace part2
{
void experimentalStuff(Machine machine)
{
    /**
     * Dump graphviz dot file - so we can visualize the machine ans solve it
     * manually.
     * It also obvious that there is a pattern that we cold check for and find
     * broken parts. Even more obvious that all z except last are obtained using
     * XOR - so it points us to 3 broken places immediately.
     *
     * Another approach could be to build own device and compare with the
     * existing one.
     *
     * And the last idea - add numbers and find bit where the result is wrong,
     * brute force nodes around until it's fixed, find next broken bit.
     */
    fmt::print("X Value: {}\n", machine.getNumericValue('x'));
    fmt::print("Y Value: {}\n", machine.getNumericValue('y'));

    using namespace graphviz;
    Digraph digraph{"ArithmeticMachine"};
    for (const auto& [name, value] : machine.values)
    {
        digraph.addNode(fmt::format("{}inputs", name[0]),
                        {name, fmt::format("{}: {}", name, value)});
    }
    for (const auto& operation : machine.operations)
    {
        digraph.addNode(operation.output[0] == 'z' ? "output" : "operations",
                        {operation.output,
                         fmt::format("{}: {}",
                                     operation.output,
                                     operation.operation == Machine::Op::AND ? "AND"
                                     : operation.operation == Machine::Op::OR ? "OR"
                                                                              : "XOR")});
        digraph.addEdge(operation.input1, operation.output);
        digraph.addEdge(operation.input2, operation.output);
    }
    std::ofstream out("graph.dot");
    dump(out, digraph);
}
}  // namespace part2
}  // namespace aoc2024::day24

int main(int argc, char** argv)
{
    using namespace aoc2024::day24;
    using namespace ::ranges;
    if (auto args = std::span(argv, argc); args.size() > 1)
    {
        auto machine = loadFromFile(args[1]);
        fmt::print("Loaded machine with {} values and {} operations\n",
                   machine.values.size(),
                   machine.operations.size());

        fmt::print("Part I: {}\n", part1::solve(machine));

        part2::experimentalStuff(machine);
    }
    else
    {
        fmt::print("Usage: {} <filename>\n", args[0]);
    }
    return 0;
}
