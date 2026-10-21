#ifndef PARSER
#define PARSER

#include <vector>
#include <functional>
#include <string>

class Parser {
public:
    Parser();
    void parse_from_file();
    void parse_from_string(std::string inputString);

private:
    std::vector<std::string> splitStatements(std::string bodyText);
    void parseStatement(std::string statement);
    std::vector<std::string> statements;
};


#endif 