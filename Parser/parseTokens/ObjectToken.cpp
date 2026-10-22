#include "ObjectToken.hpp"

ParseToken::TokenType ObjectToken::get_type() const
{
    return ParseToken::TokenType::Object;
}