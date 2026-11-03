#include "Parser.hpp"
#include "parseTokens/ArgumentToken.hpp"
#include "parseTokens/MemberMethodToken.hpp"
#include "parseTokens/ObjectToken.hpp"
#include "parseTokens/ParseToken.hpp"
#include "parseTokens/StartToken.hpp"
#include "parseTokens/VariableToken.hpp"
#include <ranges>
#include <string_view>
#include <cctype>
#include <fstream>

Parser::Parser()
{
}

std::vector<ParseTree> Parser::parse_from_file(std::string filepath)
{
    std::ifstream file{filepath};
    if (!file) {
        throw std::runtime_error("Could not open file: " + filepath);
    }
    return parse(file);
}

std::vector<ParseTree> Parser::parse_from_string(std::string inputString)
{
    std::istringstream inputStream{inputString};
    return parse(inputStream);
}

std::vector<ParseTree> Parser::parse(std::istream& inputStream)
{
    std::vector<ParseTree> parseTrees;
    std::string statement;
    while (std::getline(inputStream, statement, ';'))
    {
        if (statement == "") continue;
        ParseNode* headNode = new ParseNode(new StartToken("StatementStart"), nullptr);
        ParseTree parseTree{headNode};
        std::istringstream inputStream{statement};
        parse_statement(headNode, inputStream);
        parseTrees.push_back(parseTree);
    }
    return parseTrees;
}

void Parser::parse_statement(ParseNode* parentNode, std::istream& statement)
{
    std::ostringstream tokenText;
    char character;
    while (statement.get(character))
    {
        if (character == '(')
        {
            parse_on_left_parenthases_delimeter(parentNode, statement, tokenText);
        }
        else if (character == ')')
        {
            parse_on_right_parenthases_delimeter(parentNode, statement, tokenText);
            return;
        }
        else if (character == '.')
        {
            parentNode = parse_on_dot_delimeter(parentNode, statement, tokenText);
        }
        else if (character == ',')
        {
            parse_on_comma_delimeter(parentNode, statement, tokenText);
        }
        else if (character == '=')
        {
            parse_on_equals_delimeter(parentNode, statement, tokenText);
        }
        else if (character != '\n' && character != ' ') {
            tokenText << character;
        }
    }
    parse_on_end_of_statement(parentNode, statement, tokenText);
}

void Parser::do_member_method_add(ParseNode* parentNode, std::string methodText)
{
    ParseNode* grandparentNode = parentNode->get_parent();
    auto parentNodeUniquePtr = grandparentNode->pop_last_child();
    grandparentNode->add_child(new MemberMethodToken(methodText));
    ParseNode* memberMethodNode = grandparentNode->get_children().back().get();
    memberMethodNode->add_child_from_node(std::move(parentNodeUniquePtr));
}

ParseNode* Parser::parse_on_dot_delimeter(ParseNode *parentNode, std::istream &inputStream, std::ostringstream &tokenText)
{
    if (!std::isdigit(static_cast<unsigned char>(tokenText.str().front())) 
                && !std::isdigit(static_cast<unsigned char>(inputStream.peek())))
    {
        previousDelimeter = '.';
        std::string previousToken = tokenText.str();
        if (previousToken == "")
        {
            parentNode = parentNode->get_children().back().get();
            return parentNode;
        }
        parentNode->add_child(new VariableToken(previousToken)); // This is adding just the VariableToken, Not its children
        ParseNode* newNode = parentNode->get_children().back().get();
        parse_statement(newNode, inputStream);
        tokenText.str("");
    }
    else
    {
        tokenText << '.';
    }
    return parentNode;
}


void Parser::parse_on_comma_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText)
{
    if (tokenText.str() == "") return;
    parentNode->add_child(new ArgumentToken(tokenText.str()));
    tokenText.str("");
    previousDelimeter = ',';
}

void Parser::parse_on_left_parenthases_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText)
{
    ParseNode* callNode = nullptr;
    if (previousDelimeter == '.')
    {
        parentNode->add_child(new MemberMethodToken(tokenText.str()));
        parentNode->swap_positions_with_last_child();
        callNode = parentNode->get_parent();
    }
    else
    {
        parentNode->add_child(new ObjectToken(tokenText.str()));
        callNode = parentNode->get_children().back().get();
    }
    previousDelimeter = '(';
    parse_statement(callNode, inputStream);
    tokenText.str("");
}

void Parser::parse_on_equals_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText)
{
    parentNode->add_child(new VariableToken(tokenText.str()));
    ParseNode* newNode = parentNode->get_children().back().get();
    previousDelimeter = '=';
    parse_statement(newNode, inputStream);
    tokenText.str("");
}

void Parser::parse_on_right_parenthases_delimeter(ParseNode *parentNode, std::istream &inputStream, std::ostringstream &tokenText)
{
    parentNode->add_child(new ArgumentToken(tokenText.str()));
    previousDelimeter = ')';
}

void Parser::parse_on_end_of_statement(ParseNode *parentNode, std::istream &inputStream, std::ostringstream &tokenText)
{
    if (tokenText.str() == "")
    {
        return;
    }
    parentNode->add_child(new ArgumentToken(tokenText.str()));
}
