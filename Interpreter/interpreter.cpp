#include "Interpreter.hpp"
#include <algorithm>
#include "ObjectFactory.hpp"
#include <iostream>
#include "ViewerAPI.hpp"
#include "InterpreterException.hpp"

Interpreter::Interpreter(Context* context) : context{context}
{
}

void Interpreter::interpret_trees(std::vector<ParseTree> trees)
{
    for (ParseTree tree : trees)
    {
        std::cout << "Interpreting tree: " << tree.to_string() << std::endl;
        interpret(tree);
    }
}

void Interpreter::interpret(ParseTree tree)
{
    ParseNode* head = tree.get_head_node();
    evaluate_node(head);
}

ParseNode* Interpreter::find_deepest_leaf(std::map<ParseNode*, int> leafMap)
{
    if (!leafMap.empty()) 
    {
        auto max = std::max_element(
            leafMap.begin(), 
            leafMap.end(), 
            [](const auto& a, const auto& b) 
                {
                return a.second < b.second;
                }
        );
        return max->first;
    }
    return nullptr;
}

RuntimeValue Interpreter::evaluate_node(ParseNode* node)
{
    ParseToken::TokenType nodeType = node->get_value()->get_type();
    switch(nodeType) {
        case ParseToken::TokenType::Start:
            return evaluate_start_node(node);
        case ParseToken::TokenType::Object:
            return evaluate_object_node(node);
        case ParseToken::TokenType::Argument:
            return evaluate_argument_node(node);
        case ParseToken::TokenType::Variable:
            return evaluate_variable_node(node);
        case ParseToken::TokenType::MemberMethod:
            return evaluate_member_method_node(node);
    }
}

RuntimeValue Interpreter::evaluate_start_node(ParseNode *node)
{
    const auto& children = node->get_children();
    for (const auto& child : children)
    {
        evaluate_node(child.get());
    }
    return RuntimeValue{};
}

RuntimeValue Interpreter::evaluate_object_node(ParseNode* node)
{
    std::vector<RuntimeValue> args;
    const auto& children = node->get_children();
    for (const auto& child : children)
    {
        args.push_back(evaluate_node(child.get()));
    }
    auto object = factory.create(node->get_value()->getTokenText(), args);
    return RuntimeValue(std::move(object));
}

RuntimeValue Interpreter::evaluate_argument_node(ParseNode* node)
{
    std::string tokenText = node->get_value()->getTokenText();
    try {
        return RuntimeValue{std::stod(tokenText)};
    }
    catch (const std::invalid_argument& e) {
        return context->get(tokenText);
    }
}

RuntimeValue Interpreter::evaluate_variable_node(ParseNode* node)
{
    const auto& children = node->get_children();
    std::string variableName = node->get_value()->getTokenText();
    if (children.size() == 0) 
    {
        return RuntimeValue(context->get(variableName));
    }
    else if (children.size() == 1)
    {
        RuntimeValue variableValue = RuntimeValue(evaluate_node(children[0].get()));
        context->add(variableName, variableValue);
        return variableValue;
    }
    throw std::runtime_error("Cannot assign variable to more than one value!");
}

RuntimeValue Interpreter::evaluate_member_method_node(ParseNode* node)
{
    std::vector<RuntimeValue> args;
    const auto& children = node->get_children();
    for (const auto& child : children)
    {
        args.push_back(evaluate_node(child.get()));
    }
    RuntimeValue memberObject = args[0];
    if (memberObject.is<RuntimeValue::ViewerAPIPointer>())
    {
        auto retrieved = memberObject.as<RuntimeValue::ViewerAPIPointer>();
        auto storedObject = std::dynamic_pointer_cast<ViewerAPI>(retrieved);
        std::string method = node->get_value()->getTokenText();
        if (!args.empty()) {
            args.erase(args.begin());
        }
        return storedObject->invoke(method, args);
    }
    else if (memberObject.is<RuntimeValue::MesherPointer>())
    {
        auto retrieved = memberObject.as<RuntimeValue::MesherPointer>();
        auto storedObject = std::dynamic_pointer_cast<Mesher>(retrieved);
        std::string method = node->get_value()->getTokenText();
        return storedObject->invoke(method, args);
    }
    else 
    {
        auto retrieved = memberObject.as<RuntimeValue::CADObjectPointer>();
        auto storedObject = std::dynamic_pointer_cast<Object3d>(retrieved);
        std::string method = node->get_value()->getTokenText();
        if (!args.empty()) {
            args.erase(args.begin());
        }
        return storedObject->invoke(method, args);
    }
}
