#include "gtest/gtest.h"
#include "Interpreter.hpp"
#include "primitives3d/Cube.hpp"
#include "primitives3d/Object3d.hpp"
#include "Parser.hpp"
#include "ParseTree.hpp"
#include <vector>
#include <string>

TEST(interpreter, GivenABasicCubeCodeInput_WhenInterpreting_ExpectBasicCubeOutput)
{
    std::string input{"Cube(1,1,1);"};
    Interpreter interpreter;
    Parser parser;
    std::vector<ParseTree> trees = parser.parse_from_string(input);
    Object3d* interpretedObject = interpreter.interpret(trees[0]);
    Cube expectedCube{1,1,1};

    ASSERT_EQ(*interpretedObject, expectedCube);
}