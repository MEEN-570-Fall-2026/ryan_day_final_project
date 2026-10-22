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
    const std::vector<std::unique_ptr<ParseNode>>& get_children() const;
    ParseToken* get_value();

    bool operator==(const ParseNode& other) const;
    bool operator!=(const ParseNode& other) const;

private:
    std::vector<std::unique_ptr<ParseNode>> childrenNodes;
    ParseNode* parentNode;  
    ParseToken* value;

};

#endif