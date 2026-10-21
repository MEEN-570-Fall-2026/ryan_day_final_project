#ifndef PARSENODE
#define PARSENODE

#include "ParseToken.hpp"
#include <vector>
#include <memory>

class ParseNode {
public:
    ParseNode(ParseToken value, ParseNode* parent);
    void add_child(ParseToken value);


private:
    std::vector<std::unique_ptr<ParseNode>> childrenNodes;
    ParseNode* parentNode;  
    ParseToken value;

};

#endif