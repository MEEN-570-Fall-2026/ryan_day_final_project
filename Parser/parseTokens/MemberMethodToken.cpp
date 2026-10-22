#include "MemberMethodToken.hpp"

ParseToken::TokenType MemberMethodToken::get_type() const
{
    return ParseToken::TokenType::MemberMethod;
}