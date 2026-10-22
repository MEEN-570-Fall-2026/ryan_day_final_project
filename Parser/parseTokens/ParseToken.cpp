#include "ParseToken.hpp"

ParseToken::ParseToken(std::string tokenText) : tokenText{tokenText}
{
}

std::string ParseToken::getTokenText()
{
    return tokenText;
}

bool ParseToken::operator==(const ParseToken &other) const
{
    if (tokenText != other.tokenText && get_type() == other.get_type())
    {
        return false;
    }
    return true;
}

bool ParseToken::operator!=(const ParseToken &other) const
{
    return !operator==(other);
}

