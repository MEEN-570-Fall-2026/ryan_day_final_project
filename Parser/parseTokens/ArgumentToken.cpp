#include "ArgumentToken.hpp"

ParseToken::TokenType ArgumentToken::get_type() const
{
    return ParseToken::TokenType::Argument;
}