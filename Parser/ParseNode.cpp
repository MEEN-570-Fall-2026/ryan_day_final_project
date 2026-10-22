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

const std::vector<std::unique_ptr<ParseNode>>& ParseNode::get_children() const
{
    return childrenNodes;
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
