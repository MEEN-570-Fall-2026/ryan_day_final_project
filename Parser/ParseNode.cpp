#include "ParseNode.hpp"
#include "parseTokens/ParseToken.hpp"

ParseNode::ParseNode(ParseToken* value, ParseNode* parent) : value{value}, parentNode{parent}
{
}

ParseNode::~ParseNode()
{
    delete value;
}

void ParseNode::add_child(ParseToken* childToken)
{
    std::unique_ptr<ParseNode> childNode = std::make_unique<ParseNode>(childToken, this);
    childrenNodes.push_back(std::move(childNode));
}

void ParseNode::add_child_from_node(std::unique_ptr<ParseNode> node)
{
    childrenNodes.push_back(std::move(node));
}

const std::vector<std::unique_ptr<ParseNode>>& ParseNode::get_children() const
{
    return childrenNodes;
}

void ParseNode::swap_positions_with_last_child()
{
    if (parentNode == nullptr)
    {
        throw std::logic_error("Cannot promote a child of the root without access to the root owner.");
    }
    if (childrenNodes.empty())
    {
        throw std::runtime_error("Node has no children!");
    }
    ParseNode* oldParent = parentNode;
    auto it = std::find_if(
        oldParent->childrenNodes.begin(),
        oldParent->childrenNodes.end(),
        [this](const std::unique_ptr<ParseNode>& node)
        {
            return node.get() == this;
        });
    if (it == oldParent->childrenNodes.end())
    {
        throw std::logic_error("Parent does not own this node.");
    }
    auto oldNode = std::move(*it);    
    auto promoted = std::move(childrenNodes.back());
    childrenNodes.pop_back();
    promoted->parentNode = oldParent;
    oldNode->parentNode = promoted.get();
    *it = std::move(promoted);            
    (*it)->childrenNodes.push_back(std::move(oldNode));
}

std::unique_ptr<ParseNode> ParseNode::pop_last_child()
{
    if (childrenNodes.size() == 0)
    {
        throw std::runtime_error("Node has no children!");
    }
    auto lastChild = std::move(childrenNodes.back());
    childrenNodes.pop_back();
    return lastChild;
}

ParseNode* ParseNode::get_parent()
{
    return parentNode;
}

ParseToken* ParseNode::get_value()
{
    return value;
}

bool ParseNode::operator==(const ParseNode &other) const
{
    if (*value != *other.value || childrenNodes.size() != other.childrenNodes.size())
    {
        return false;
    }
    for (int i = 0; i < childrenNodes.size(); i++)
    {
        if (*childrenNodes[i] != *other.childrenNodes[i])
        {
            return false;
        }
    }
    return true;
}

bool ParseNode::operator!=(const ParseNode &other) const
{
    return !operator==(other);
}
