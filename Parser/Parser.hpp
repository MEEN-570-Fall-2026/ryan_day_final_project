#ifndef PARSER
#define PARSER

#include <vector>
#include <functional>
#include <string>
#include "ParseTree.hpp"

class Parser {
public:
    Parser();
    std::vector<ParseTree> parse_from_file();
    std::vector<ParseTree> parse_from_string(std::string inputString);

private:
    void parseStatement(std::string statement);
    std::vector<std::string> statements;
};


#endif 