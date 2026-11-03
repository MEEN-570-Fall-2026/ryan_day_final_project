#include "gtest/gtest.h"
#include "Interpreter.hpp"
#include "primitives3d/Cube.hpp"
#include "primitives3d/Object3d.hpp"
#include "Parser.hpp"
#include "ParseTree.hpp"
#include "Context.hpp"
#include "RuntimeValue.hpp"
#include <vector>
#include <string>


TEST(Context, GivenARuntimeValue_WhenAddingToContext_ExpectRuntimeValueCorrectlyStoredInContext)
{
    Context context;
    std::string variableName{"theCube"};
    Cube* cubeObject = new Cube{1, 1, 1};
    RuntimeValue cubeRuntime{cubeObject};
    context.add(variableName, cubeRuntime);
}


TEST(Interpreter, GivenABasicCubeCodeInput_WhenInterpreting_ExpectCubeObjectIsAddedToContext)
{
    std::string input{"theCube = Cube(1,1,1);"};
    Context context;
    Interpreter interpreter{context};
    Parser parser;
    std::vector<ParseTree> trees = parser.parse_from_string(input);
    interpreter.interpret_parse_tree(trees[0]);
    Cube expectedCube{1, 1, 1};

    ASSERT_EQ(*context["theCube"], expectedCube);
}