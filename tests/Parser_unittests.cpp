#include "gtest/gtest.h"
#include "Parser.hpp"
#include <string>


bool checkExpectedCommandsWithActualCommands(std::vector<Command*> expectedCommands, std::vector<Command*> actualCommands)
{
    if (expectedCommands.size() != actualCommands.size())
    {
        return false;
    }
    for (int i = 0; i < expectedCommands.size(); i++)
    {
        if (*expectedCommands[i] != *actualCommands[i])
        {
            return false;
        }
    }
    return true;
}


TEST(Parser, GivenAStringInput_WhenParsingSingleLine_ExpectCallableCreated)
{
    Parser parser;
    std::string inputString = "Cube(1,1,1);";
    std::vector<Command*> actualCommands = parser.parse_from_string(inputString);

    std::vector<Command*> expectedCommands = {
        new CubeCommand()
    }
    ASSERT_TRUE(checkExpectedCommandsWithActualCommands(expectedCommands, actualCommands))
}