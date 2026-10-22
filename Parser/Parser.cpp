#include "Parser.hpp"
#include <ranges>
#include <string_view>
#include <cctype>

Parser::Parser()
{
}

std::vector<ParseTree> Parser::parse_from_file()
{
}

std::vector<ParseTree> Parser::parse_from_string(std::string inputString)
{
    return parse(std::istringstream(inputString));
}

std::vector<ParseTree> Parser::parse(std::istringstream inputStream)
{
    std::vector<ParseTree> parseTrees;
    std::string statement;
    while (std::getline(inputStream, statement, ';'))
    {
        if (statement == "") continue;
        ParseNode* headNode = new ParseNode(ParseToken("StatementStart"), nullptr);
        ParseTree parseTree{headNode};
        std::istringstream inputStream{statement};
        parse_statement(headNode, inputStream);
        parseTrees.push_back(parseTree);
    }
    return parseTrees;
}

void Parser::parse_statement(ParseNode* parentNode, std::istringstream& statement)
{
    std::ostringstream tokenText;
    char character;
    while (statement.get(character))
    {
        if (character == '(')
        {
            parentNode->add_child(tokenText.str());
            ParseNode* newNode = parentNode->get_children().back().get();
            parse_statement(newNode, statement);
            tokenText.str("");
        }
        else if (character == ')')
        {
            parentNode->add_child(tokenText.str());
            return;
        }
        else if (character == '.')
        {
            if (!std::isdigit(tokenText.str().front()))
            {
                parentNode->add_child(tokenText.str());
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
            parentNode->add_child(tokenText.str());
            tokenText.str("");
        }
        else if (character != '\n' && character != ' ') {
            tokenText << character;
        }
    }
}
