#ifndef ARGUMENTTOKEN
#define ARGUMENTTOKEN

#include "parseTokens/ParseToken.hpp"

class ArgumentToken : public ParseToken {
    public:
        using ParseToken::ParseToken;
        TokenType get_type() const override;

    private:
        TokenType type = TokenType::Argument;
};

#endif