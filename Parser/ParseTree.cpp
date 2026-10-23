#include "ParseTree.hpp"

#include <sstream>

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


namespace
{
std::string token_type_name(ParseToken::TokenType type)
{
    using TokenType = ParseToken::TokenType;

    switch (type)
    {
        case TokenType::Object:       return "Object";
        case TokenType::Argument:     return "Argument";
        case TokenType::Variable:     return "Variable";
        case TokenType::MemberMethod: return "MemberMethod";
        case TokenType::Start:        return "Start";
    }

    return "Unknown";
}
}

void ParseTree::append_node(std::ostringstream& out,
                            ParseNode* node,
                            const std::string& prefix,
                            bool is_last,
                            bool is_root)
{
    if (node == nullptr)
    {
        out << prefix << (is_last ? "└── " : "├── ") << "<null>\n";
        return;
    }

    auto* token = node->get_value();

    const std::string label =
        token ? token->getTokenText() : "<null token>";
    const std::string type =
        token ? token_type_name(token->get_type()) : "<null type>";

    const std::string node_text = label + " [" + type + "]";

    if (is_root)
    {
        out << node_text << '\n';
    }
    else
    {
        out << prefix << (is_last ? "└── " : "├── ")
            << node_text << '\n';
    }

    const auto& children = node->get_children();
    const std::string child_prefix =
        is_root ? "" : prefix + (is_last ? "    " : "│   ");

    for (std::size_t i = 0; i < children.size(); ++i)
    {
        append_node(out, children[i].get(), child_prefix,
                    i + 1 == children.size(), false);
    }
}

std::string ParseTree::to_string()
{
    std::ostringstream out;
    append_node(out, headNode, "", true, true);
    return out.str();
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
