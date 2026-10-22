#include "StartToken.hpp"

ParseToken::TokenType StartToken::get_type() const
{
    return ParseToken::TokenType::Start;
}