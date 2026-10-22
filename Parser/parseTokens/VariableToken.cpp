#include "VariableToken.hpp"

ParseToken::TokenType VariableToken::get_type() const
{
    return ParseToken::TokenType::Variable;
}