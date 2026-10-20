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
    void parse_fe_cad_code();

};


#endif 