#ifndef PARSETREE
#define PARSETREE

#include "ParseNode.hpp"
#include <vector>
#include <map>

class ParseTree {
public:
    ParseTree(ParseNode* headNode);
    ParseNode* get_head_node();
    std::map<ParseNode*, int> get_leaf_nodes();

private:
    ParseNode* headNode;
    std::map<ParseNode*, int> leafNodes;
    
    void update_leaf_nodes();
    void find_new_leaves(ParseNode*, int startingDepth);

};


#endif