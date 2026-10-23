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
    std::vector<ParseTree> parse_from_file(std::string filepath);
    std::vector<ParseTree> parse_from_string(std::string inputString);

private:
    std::vector<ParseTree> parse(std::istream& inputStream);
    void parse_statement(ParseNode* parentNode, std::istream& statement);
    std::vector<std::string> statements;
    char previousDelimeter;
    void parse_on_dot_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText);
    void parse_on_comma_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText);
    void parse_on_left_parenthases_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText);
    void parse_on_equals_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText);
    void parse_on_right_parenthases_delimeter(ParseNode* parentNode, std::istream& inputStream, std::ostringstream& tokenText);


};


#endif 