#ifndef MEMBERMETHODTOKEN
#define MEMBERMETHODTOKEN

#include "parseTokens/ParseToken.hpp"

class MemberMethodToken : public ParseToken {
    public:
        using ParseToken::ParseToken;
        TokenType get_type() const override;
};

#endif