#ifndef PARSER
#define PARSER

#include <vector>
#include <functional>
#include <string>
#include "Command.hpp"

class Parser {
public:
    Parser();
    void parse_from_file();
    void parse_from_string(std::string inputString);

private:
    std::vector<std::string> splitStatements(std::string bodyText);
    Command parseStatement(std::string statement);
    std::vector<std::string> statements;
    std::vector<Command> commands;
};


#endif 