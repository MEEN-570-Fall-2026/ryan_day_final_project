#ifndef PARSENODE
#define PARSENODE

#include "parseTokens/ParseToken.hpp"
#include <vector>
#include <memory>

class ParseNode {
public:
    ParseNode(ParseToken* value, ParseNode* parent);
    ~ParseNode();
    void add_child(ParseToken* value);
    void add_child_from_node(std::unique_ptr<ParseNode> node);
    const std::vector<std::unique_ptr<ParseNode>>& get_children() const;
    void swap_positions_with_last_child();
    std::unique_ptr<ParseNode> pop_last_child();
    ParseNode* get_parent();
    ParseToken* get_value();

    bool operator==(const ParseNode& other) const;
    bool operator!=(const ParseNode& other) const;

private:
    std::vector<std::unique_ptr<ParseNode>> childrenNodes;
    ParseNode* parentNode;  
    ParseToken* value;

};

#endif