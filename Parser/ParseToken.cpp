#include "ParseToken.hpp"

ParseToken::ParseToken(std::string tokenText) : tokenText{tokenText}
{
}

std::string ParseToken::getTokenText()
{
    return tokenText;
}
