#ifndef PARSETOKEN
#define PARSETOKEN

#include <string>

class ParseToken {
    public:
        ParseToken(std::string tokenText);
        virtual ~ParseToken() = default;
        std::string getTokenText();

        bool operator==(const ParseToken& other) const;
        bool operator!=(const ParseToken& other) const;

        enum class TokenType {
            Object,
            Argument,
            Variable,
            MemberMethod,
            Start
        };

        virtual TokenType get_type() const = 0;

    protected:
        std::string tokenText;
        TokenType type;
};

#endif