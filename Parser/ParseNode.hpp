#ifndef PARSENODE
#define PARSENODE

#include "ParseToken.hpp"
#include <vector>
#include <memory>

class ParseNode {
public:
    ParseNode(ParseToken value, ParseNode* parent);
    void add_child(ParseToken value);
    std::vector<std::unique_ptr<ParseNode>> get_children();


private:
    std::vector<std::unique_ptr<ParseNode>> childrenNodes;
    ParseNode* parentNode;  
    ParseToken value;

};

#endif