#ifdef PARSENODE
#define PARSENODE

#include "ParseToken.hpp"

class ParseNode {
public:
    ParseNode(ParseToken value, ParseNode* parent);
    void add_child(ParseToken value);


private:
    std::vector<ParseNode*> childrenNodes;
    ParseNode* parentNode;  
    ParseToken value;

};

#endif