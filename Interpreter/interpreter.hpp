#ifndef INTERPRETERFECAD
#define INTERPRETERFECAD

#include "ParseTree.hpp"
#include <map>
#include <string>
#include "primitives3d/Object3d.hpp"
#include "Context.hpp"
#include "ObjectFactory.hpp"

class Interpreter {
    public:
        Interpreter(Context* context);
        void interpret(ParseTree tree);

    private:
        std::map<std::string, Object3d*> objects3dVariableMap;
        ParseNode* find_deepest_leaf(std::map<ParseNode*, int> leafMap);
        RuntimeValue evaluate_node(ParseNode* node);
        RuntimeValue evaluate_start_node(ParseNode* node);
        RuntimeValue evaluate_object_node(ParseNode* node);
        RuntimeValue evaluate_argument_node(ParseNode* node);
        RuntimeValue evaluate_variable_node(ParseNode* node);
        RuntimeValue evaluate_member_method_node(ParseNode* node);
        Context* context{nullptr};

        ObjectFactory factory;
};

#endif