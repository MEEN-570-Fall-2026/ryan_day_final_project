#include "ParseTree.hpp"

ParseTree::ParseTree(ParseNode* headNode) : headNode{headNode}
{
    update_leaf_nodes();
}

ParseNode* ParseTree::get_head_node()
{
    return headNode;
}

std::map<ParseNode *, int> ParseTree::get_leaf_nodes()
{
    update_leaf_nodes();
    return leafNodes;
}

bool ParseTree::operator==(const ParseTree &other) const
{
    if (*headNode != *other.headNode)
    {
        return false;
    }
    return true;
}

bool ParseTree::operator!=(const ParseTree &other) const
{
    return !operator==(other);
}

void ParseTree::update_leaf_nodes()
{
    leafNodes.clear();
    find_new_leaves(headNode, 0);
}

void ParseTree::find_new_leaves(ParseNode* oldLeaf, int depth)
{
    if (oldLeaf->get_children().size() == 0) {
        leafNodes[oldLeaf] = depth;
        return;
    }
    for (const auto& child : oldLeaf->get_children())
    {
        find_new_leaves(child.get(), depth + 1);
    }
}
