#ifndef PARSETOKEN
#define PARSETOKEN

#include <string>

class ParseToken {
    public:
        ParseToken(std::string tokenText);
        std::string getTokenText();

    private:
        std::string tokenText;
};

#endif