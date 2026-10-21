#include "Parser.hpp"
#include <ranges>
#include <string_view>

Parser::Parser()
{
}

std::vector<ParseTree> Parser::parse_from_file()
{
}

std::vector<ParseTree> Parser::parse_from_string(std::string inputString)
{
    for (std::string statement : statements)
    {
        parseStatement(statement);
    }
}


void Parser::parseStatement(std::string statement)
{
    int subStatementStart = 0;
    for (int i = 0; i < statement.length(); i++)
    {
        
    }
}
