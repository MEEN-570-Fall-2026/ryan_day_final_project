#include "Parser.hpp"
#include <ranges>
#include <string_view>

Parser::Parser()
{
}

void Parser::parse_from_file()
{
}

void Parser::parse_from_string(std::string inputString)
{
    splitStatements(inputString);
    for (std::string statement : statements)
    {
        parseStatement(statement);
    }
}

std::vector<std::string> Parser::splitStatements(std::string bodyText)
{
    for (std::string statement : std::views::split(bodyText, ";"))
    {
        statements.push_back(statement);
    }
}

void Parser::parseStatement(std::string statement)
{
    int subStatementStart = 0;
    for (int i = 0; i < statement.length(); i++)
    {
        
    }
}
