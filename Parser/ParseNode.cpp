#include "ParseNode.hpp"
#include "ParseToken.hpp"

ParseNode::ParseNode(ParseToken value, ParseNode* parent) : value{value}, parentNode{parent}
{
}

void ParseNode::add_child(ParseToken childToken)
{
    std::unique_ptr<ParseNode> childNode = std::make_unique<ParseNode>(childToken, this);
    childrenNodes.push_back(childNode);
}

