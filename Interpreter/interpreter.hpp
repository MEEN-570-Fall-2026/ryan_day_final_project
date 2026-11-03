#ifndef INTERPRETERFECAD
#define INTERPRETERFECAD

#include "ParseTree.hpp"
#include <map>
#include <string>
#include "primitives3d/Object3d.hpp"

class Interpreter {
    public:
        Interpreter();
        void interpret(ParseTree* tree);
        Object3d* interpret_parse_tree(ParseTree tree);

    private:
        std::map<std::string, Object3d*> objects3dVariableMap;
        ParseNode* find_deepest_leaf(std::map<ParseNode*, int> leafMap);
        void interpret_parse_node(ParseNode* node);

};

#endif