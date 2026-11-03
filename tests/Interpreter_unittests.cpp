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
#include <memory>


TEST(Context, GivenARuntimeValue_WhenAddingToContext_ExpectRuntimeValueCorrectlyStoredInContext)
{
    Context context;
    std::string variableName{"theCube"};
    std::shared_ptr<CADObject> cubeObject = std::make_shared<Cube>(1, 1, 1);
    RuntimeValue cubeRuntime{cubeObject};
    context.add(variableName, cubeRuntime);

    auto retrieved = context.get(variableName).as<RuntimeValue::CADObjectPointer>();
    auto storedObject = std::dynamic_pointer_cast<Object3d>(retrieved);

    ASSERT_EQ(*storedObject, Cube(1, 1, 1));
}


TEST(Context, GivenARuntimeValuePrimitive_WhenAddingToContext_expectRuntimeValueCorrectlyStoredInContext)
{
    Context context;
    std::string variableName{"aNumber"};
    int value = 1;
    RuntimeValue intRuntime{value};
    context.add(variableName, intRuntime);

    auto retrieved = context.get(variableName).as<int>();

    ASSERT_EQ(retrieved, value);
}


// TEST(Interpreter, GivenABasicCubeCodeInput_WhenInterpreting_ExpectCubeObjectIsAddedToContext)
// {
//     std::string input{"theCube = Cube(1,1,1);"};
//     Context context;
//     Interpreter interpreter{context};
//     Parser parser;
//     std::vector<ParseTree> trees = parser.parse_from_string(input);
//     interpreter.interpret_parse_tree(trees[0]);
//     Cube expectedCube{1, 1, 1};

//     ASSERT_EQ(*context["theCube"], expectedCube);
// }