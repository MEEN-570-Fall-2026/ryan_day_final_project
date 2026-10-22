#ifndef STARTTOKEN
#define STARTTOKEN

#include "parseTokens/ParseToken.hpp"

class StartToken : public ParseToken {
    public:
        using ParseToken::ParseToken;
        TokenType get_type() const override;

    private:
        TokenType type = TokenType::Start;
};

#endif