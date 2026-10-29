#include "Interpreter.hpp"
#include <algorithm>

Interpreter::Interpreter()
{
}

void Interpreter::interpret(ParseTree* tree)
{
    std::map<ParseNode*, int> leaves = tree->get_leaf_nodes();
    ParseNode* deepestLeaf = find_deepest_leaf(leaves);
}

ParseNode* Interpreter::find_deepest_leaf(std::map<ParseNode*, int> leafMap)
{
    if (!leafMap.empty()) 
    {
        auto max = std::max_element(
            leafMap.begin(), 
            leafMap.end(), 
            [](const auto& a, const auto& b) 
                {
                return a.second < b.second;
                }
        );
        return max->first;
    }
}