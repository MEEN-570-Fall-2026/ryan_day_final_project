#ifndef OBJECTTOKEN
#define OBJECTTOKEN

#include "parseTokens/ParseToken.hpp"

class ObjectToken : public ParseToken {
    public:
        using ParseToken::ParseToken;
        TokenType get_type() const override;

    private:
        TokenType type = TokenType::Object;
};

#endif