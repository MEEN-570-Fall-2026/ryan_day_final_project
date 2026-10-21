#include "ParseNode.hpp"
#include "ParseToken.hpp"

ParseNode::ParseNode(ParseToken value, ParseNode* parent) : value{value}, parentNode{parent}
{
}

void ParseNode::add_child(ParseToken childToken)
{
    std::unique_ptr<ParseNode> childNode = std::make_unique<ParseNode>(childToken, this);
    childrenNodes.push_back(std::move(childNode));
}

const std::vector<std::unique_ptr<ParseNode>>& ParseNode::get_children() const
{
    return childrenNodes;
}

ParseToken ParseNode::get_value()
{
    return value;
}
