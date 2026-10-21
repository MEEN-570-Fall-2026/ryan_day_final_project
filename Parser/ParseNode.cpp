#include "ParseNode.hpp"
#include "ParseToken.hpp"

ParseNode::ParseNode(ParseToken value) : value{value}
{
}

void ParseNode::add_child(ParseToken childToken)
{
    ParseNode* childNode = new ParseNode(childToken, this);
    childrenNodes.push_back(childNode);
}

ParseNode::~ParseNode()
{
    for (ParseNode* child : childrenNodes)
    {
        delete child;
    }
    delete parentNode;
}
