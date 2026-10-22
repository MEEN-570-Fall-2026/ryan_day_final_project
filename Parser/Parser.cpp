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
            parentNode->add_child(new ArgumentToken(tokenText.str()));
            ParseNode* newNode = parentNode->get_children().back().get();
            parse_statement(newNode, statement);
            tokenText.str("");
        }
        else if (character == ')')
        {
            parentNode->add_child(new ArgumentToken(tokenText.str()));
            return;
        }
        else if (character == '.')
        {
            if (!std::isdigit(static_cast<unsigned char>(tokenText.str().front())) 
                && !std::isdigit(static_cast<unsigned char>(statement.peek())))
            {
                std::string previousToken = tokenText.str();
                if (previousToken == "")
                {
                    parentNode = parentNode->get_children().back().get();
                    continue;
                }
                parentNode->add_child(new MemberMethodToken(previousToken));
                ParseNode* newNode = parentNode->get_children().back().get();
                parse_statement(newNode, statement);
                tokenText.str("");
            }
            else
            {
                tokenText << character;
            }
        }
        else if (character == ',')
        {
            if (tokenText.str() == "") continue;
            parentNode->add_child(new ArgumentToken(tokenText.str()));
            tokenText.str("");
        }
        else if (character == '=')
        {
            parentNode->add_child(new VariableToken(tokenText.str()));
            ParseNode* newNode = parentNode->get_children().back().get();
            parse_statement(newNode, statement);
            tokenText.str("");
        }
        else if (character != '\n' && character != ' ') {
            tokenText << character;
        }
    }
}

