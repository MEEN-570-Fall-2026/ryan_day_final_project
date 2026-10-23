#ifndef PARSETREE
#define PARSETREE

#include "ParseNode.hpp"
#include <vector>
#include <map>
#include <string>

class ParseTree {
public:
    ParseTree(ParseNode* headNode);
    ParseNode* get_head_node();
    std::map<ParseNode*, int> get_leaf_nodes();

    bool operator==(const ParseTree& other) const;
    bool operator!=(const ParseTree& other) const;

    std::string to_string();
    void append_node(std::ostringstream& out,
        ParseNode* node,
        const std::string& prefix,
        bool is_last,
        bool is_root);
    void PrintTo(const ParseTree& tree, std::ostream* os);

private:
    ParseNode* headNode;
    std::map<ParseNode*, int> leafNodes;
    
    void update_leaf_nodes();
    void find_new_leaves(ParseNode*, int startingDepth);

    

};


#endif