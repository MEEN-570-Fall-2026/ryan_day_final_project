#ifndef PARSER
#define PARSER

#include <vector>
#include <functional>
#include <string>
#include "ParseTree.hpp"
#include <sstream>

class Parser {
public:
    Parser();
    std::vector<ParseTree> parse_from_file();
    std::vector<ParseTree> parse_from_string(std::string inputString);

private:
    std::vector<ParseTree> parse(std::istringstream inputStream);
    void parse_statement(ParseNode* parentNode, std::istringstream& statement);
    std::vector<std::string> statements;
};


#endif 