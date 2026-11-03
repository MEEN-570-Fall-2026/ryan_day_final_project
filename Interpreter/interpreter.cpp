#include "Interpreter.hpp"
#include <algorithm>
#include "Interpreter.hpp"

Interpreter::Interpreter()
{
}

void Interpreter::interpret(ParseTree* tree)
{
    std::map<ParseNode*, int> leaves = tree->get_leaf_nodes();
    ParseNode* deepestLeaf = find_deepest_leaf(leaves);
    deepestLeaf->get_parent();
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

Object3d* Interpreter::interpret_parse_tree(ParseTree tree)
{
    ParseNode* deepestLeaf = find_deepest_leaf(tree.get_leaf_nodes());
    ParseNode* parentOfDeepestLeaf = deepestLeaf->get_parent();
    //interpret_parse_node(parentofDeepestLeaf);
}

void Interpreter::interpret_parse_node(ParseNode* node)
{
    //nodeType = node->get_value()->get_type();
    //auto children = node->get_children();
    
}
