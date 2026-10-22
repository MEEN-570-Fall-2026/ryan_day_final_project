#ifndef VARIABLETOKEN
#define VARIABLETOKEN

#include "parseTokens/ParseToken.hpp"

class VariableToken : public ParseToken {
    public:
        using ParseToken::ParseToken;
        TokenType get_type() const override;
};

#endif