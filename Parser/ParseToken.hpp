#ifndef PARSETOKEN
#define PARSETOKEN

#include <string>

class ParseToken {
    public:
        ParseToken(std::string tokenText);
        std::string getTokenText();

        bool operator==(const ParseToken& other) const;
        bool operator!=(const ParseToken& other) const;

    private:
        std::string tokenText;
};

#endif