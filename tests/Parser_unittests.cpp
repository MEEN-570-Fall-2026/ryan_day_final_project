#include "gtest/gtest.h"
#include "Parser.hpp"
#include <string>
#include "ParseNode.hpp"
#include "parseTokens/ParseToken.hpp"
#include "parseTokens/ArgumentToken.hpp"
#include "parseTokens/MemberMethodToken.hpp"
#include "parseTokens/ObjectToken.hpp"
#include "parseTokens/ParseToken.hpp"
#include "parseTokens/StartToken.hpp"
#include "parseTokens/VariableToken.hpp"
#include "ParseTree.hpp"
#include <format>


#include <filesystem>
#include <iostream>

ParseTree constructTreeWithHead()
{
    ParseToken* headToken = new StartToken("HeadToken");
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    return ParseTree(headNode);
}


ParseNode* addIterativeRightChildren(ParseTree& tree, int childrenLayers)
{
    ParseNode* head = tree.get_head_node();
    ParseToken* rightToken = new ArgumentToken{"RightToken0"};
    head->add_child(rightToken);
    ParseNode* rightChildNode = head->get_children().back().get();
    for (int i = 1; i < childrenLayers; i++)
    {
        ParseToken* leafTokenRight = new ArgumentToken(std::format("Leaf{}", i));
        rightChildNode->add_child(leafTokenRight);
        rightChildNode = rightChildNode->get_children().back().get();
    }
    return rightChildNode;
}


TEST(ParseTree, GivenAParseTree_WhenInitializingWithHead_ExpectHeadIsOnlyLeaf)
{
    ParseTree tree = constructTreeWithHead();
    std::map<ParseNode*, int> leaves = tree.get_leaf_nodes();
    ASSERT_EQ(leaves.size(), 1);
    ParseNode* head = tree.get_head_node();
    ASSERT_TRUE(leaves.contains(head));
}

TEST(ParseNode, GivenAParseNode_WhenAddingChildren_ExpectChildrenAddedCorrectly)
{
    ParseToken* headToken = new StartToken("HeadToken");
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseToken* child1Token = new ArgumentToken("child1");
    ParseToken* child2Token = new ArgumentToken("child2");
    headNode->add_child(child1Token);
    headNode->add_child(child2Token);
    const auto& children = headNode->get_children();
    ASSERT_EQ(children.size(), 2);
    ASSERT_EQ(children[0]->get_value()->getTokenText(), child1Token->getTokenText());
    ASSERT_EQ(children[1]->get_value()->getTokenText(), child2Token->getTokenText());
}

TEST(ParseTree, GivenAParseTree_WhenAddingNewNodes_ExpectLeavesUpdate)
{
    ParseTree tree = constructTreeWithHead();
    ParseNode* head = tree.get_head_node();
    ParseToken* leafToken1 = new ArgumentToken("Leaf1");
    ParseToken* leafToken2 = new ArgumentToken("Leaf2");
    head->add_child(leafToken1);
    head->add_child(leafToken2);
    std::map<ParseNode*, int> leaves = tree.get_leaf_nodes();
    ASSERT_EQ(leaves.size(), 2);
    const auto& children = head->get_children();
    ASSERT_TRUE(leaves.contains(children[0].get()));
    ASSERT_TRUE(leaves.contains(children[1].get()));
    ASSERT_EQ(leaves[children[0].get()], 1);
    ASSERT_EQ(leaves[children[1].get()], 1);
}

TEST(ParseTree, GivenAParseTree_WhenAddingNewUnevenNodes_ExpectLeavesUpdateCorrectly)
{
    ParseTree tree = constructTreeWithHead();
    ParseNode* head = tree.get_head_node();
    ParseToken* leafTokenLeft = new ArgumentToken("LeafLeft");
    head->add_child(leafTokenLeft);
    ParseNode* finalRightChild = addIterativeRightChildren(tree, 10);
    std::map<ParseNode*, int> leaves = tree.get_leaf_nodes();
    ASSERT_EQ(leaves.size(), 2);
    const auto& children = head->get_children();
    ASSERT_TRUE(leaves.contains(children[0].get()));
    ASSERT_TRUE(leaves.contains(finalRightChild));
    ASSERT_EQ(leaves[children[0].get()], 1);
    ASSERT_EQ(leaves[finalRightChild], 10);
}


TEST(ParseToken, GivenTwoEqualParseTokens_WhenCheckingTokenEquality_ExpectTokesEqual)
{
    ArgumentToken token1{"Value"};
    ArgumentToken token2{"Value"};
    ASSERT_EQ(token1, token2);
}


TEST(ParseToken, GivenTwoParseTokensWithEqualTextButDifferentTypes_WhenCheckingTokenEquality)
{
    ArgumentToken token1{"Value"};
    VariableToken token2{"Value"};
    ASSERT_NE(token1, token2);
}


TEST(ParseNode, GivenTwoEqualParseNodes_WhenCheckingNodeEquality_ExpectNodesEqual)
{
    ParseNode node1{new ArgumentToken{"Value"}, nullptr};
    ParseNode node2{new ArgumentToken{"Value"}, nullptr};
    ASSERT_EQ(node1, node2);
}


TEST(ParseNode, GivenTwoParseNodesWithDifferentChildren_WhenCheckingNodeEquality_ExpectNodesUnequal)
{
    ParseNode node1{new ObjectToken{"Value"}, nullptr};
    ParseNode node2{new ObjectToken{"Value"}, nullptr};
    node2.add_child(new ArgumentToken("Child"));
    ASSERT_NE(node1, node2);
}


TEST(ParseNode, GivenTwoParseNodesWithSameChildren_WhenCheckingNodeEquality_ExpectNodesEqual)
{
    ParseNode node1{new ObjectToken{"Value"}, nullptr};
    ParseNode node2{new ObjectToken{"Value"}, nullptr};
    node2.add_child(new ArgumentToken("Child"));
    node1.add_child(new ArgumentToken("Child"));
    ASSERT_EQ(node1, node2);
}


TEST(Parser, GivenASimpleInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(1,1,1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenANestedInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(Point(1,2,3),1,1,1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ObjectToken("Point"));
    ParseNode* pointToken = cubeToken->get_children().back().get();
    pointToken->add_child(new ArgumentToken{"1"});
    pointToken->add_child(new ArgumentToken{"2"});
    pointToken->add_child(new ArgumentToken{"3"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenAMultiLineArgumentInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(Point(1,2,3),1,1,1);\nPoint(1,1,1);\nCube(1,2,3);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};

    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree1{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ObjectToken("Point"));
    ParseNode* pointToken = cubeToken->get_children().back().get();
    pointToken->add_child(new ArgumentToken{"1"});
    pointToken->add_child(new ArgumentToken{"2"});
    pointToken->add_child(new ArgumentToken{"3"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});

    ParseNode* headNode2 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree2{headNode2};
    headNode2->add_child(new ObjectToken{"Point"});
    ParseNode* pointToken2 = headNode2->get_children().back().get();
    pointToken2->add_child(new ArgumentToken{"1"});
    pointToken2->add_child(new ArgumentToken{"1"});
    pointToken2->add_child(new ArgumentToken{"1"});

    ParseNode* headNode3 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree3{headNode3};
    headNode3->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken3 = headNode3->get_children().back().get();
    cubeToken3->add_child(new ArgumentToken{"1"});
    cubeToken3->add_child(new ArgumentToken{"2"});
    cubeToken3->add_child(new ArgumentToken{"3"});

    std::cout << "Expected:\n" << expectedParseTree1.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[0].to_string() << std::endl;
    ASSERT_EQ(expectedParseTree1, parseTrees[0]);
    std::cout << "Expected:\n" << expectedParseTree2.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[1].to_string() << std::endl;
    ASSERT_EQ(expectedParseTree2, parseTrees[1]);
    std::cout << "Expected:\n" << expectedParseTree3.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[2].to_string() << std::endl;
    ASSERT_EQ(expectedParseTree3, parseTrees[2]);
}


TEST(Parser, GivenASimpleInputStringWithSpaces_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(1, 1, 1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenASimpleInputStringWithNewlinesInArgument_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(\n1,\n1,\n1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenASimpleInputStringWithIndentedArgument_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "   Cube(\n1,\n1,\n1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenAMemberMethodCallInput_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "theCube.translate(1,2,3);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new VariableToken{"theCube"});
    ParseNode* variableNode = headNode->get_children().back().get();
    variableNode->add_child(new MemberMethodToken{"translate"});
    ParseNode* translateNode = variableNode->get_children().back().get();
    translateNode->add_child(new ArgumentToken{"1"});
    translateNode->add_child(new ArgumentToken{"2"});
    translateNode->add_child(new ArgumentToken("3"));
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenAMemberWithDecimals_WhenParsingInput_ExpectDecimalPointPreservedInTokens)
{
    std::string input = "theCube.translate(1.23,2.0,.3);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new VariableToken{"theCube"});
    ParseNode* variableNode = headNode->get_children().back().get();
    variableNode->add_child(new MemberMethodToken{"translate"});
    ParseNode* translateNode = variableNode->get_children().back().get();
    translateNode->add_child(new ArgumentToken{"1.23"});
    translateNode->add_child(new ArgumentToken{"2.0"});
    translateNode->add_child(new ArgumentToken(".3"));
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenAnIntializedObjectAndMemberMethodInline_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(1, 1, 1).translate(1, 1, 1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken* headToken = new ArgumentToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeNode = headNode->get_children().back().get();
    cubeNode->add_child(new ArgumentToken{"1"});
    cubeNode->add_child(new ArgumentToken{"1"});
    cubeNode->add_child(new ArgumentToken{"1"});
    cubeNode->add_child(new MemberMethodToken("translate"));
    ParseNode* translateNode = cubeNode->get_children().back().get();
    translateNode->add_child(new ArgumentToken("1"));
    translateNode->add_child(new ArgumentToken("1"));
    translateNode->add_child(new ArgumentToken("1"));
    
    std::cout << "Expected:\n" << expectedParseTree.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[0].to_string() << std::endl;

    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenATextFile_WhenParsingText_ExpectCorrectParseTree)
{
    
    std::cout << "\n\n" << std::filesystem::current_path() << "\n\n" << '\n';

    std::string filepath = "test_files/parserReadsFromFileTest.txt";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_file(filepath);
    
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree1{headNode};
    headNode->add_child(new ObjectToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});
    cubeToken->add_child(new ArgumentToken{"1"});

    ParseNode* headNode2 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree2{headNode2};
    headNode2->add_child(new ObjectToken{"Point"});
    ParseNode* pointToken2 = headNode2->get_children().back().get();
    pointToken2->add_child(new ArgumentToken{"2"});
    pointToken2->add_child(new ArgumentToken{"2.2"});
    pointToken2->add_child(new ArgumentToken{"2"});

    ASSERT_EQ(expectedParseTree1, parseTrees[0]);
    ASSERT_EQ(expectedParseTree2, parseTrees[1]);
}

TEST(Parser, GivenATextFileWithVariableAssignment_WhenParsingText_ExpectCorrectParseTree)
{
    
    std::cout << "\n\n" << std::filesystem::current_path() << "\n\n" << '\n';

    std::string filepath = "test_files/parserVariableTest.txt";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_file(filepath);
    
    ParseToken* headToken = new StartToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree1{headNode};
    headNode->add_child(new VariableToken{"centroidPoint"});
    ParseNode* variableNode = headNode->get_children().back().get();
    variableNode->add_child(new ObjectToken("Point"));
    ParseNode* pointNode = variableNode->get_children().back().get();
    pointNode->add_child(new ArgumentToken{"1"});
    pointNode->add_child(new ArgumentToken{"1"});
    pointNode->add_child(new ArgumentToken{"1"});

    ParseNode* headNode2 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree2{headNode2};
    headNode2->add_child(new VariableToken{"theCube"});
    ParseNode* variableNode2 = headNode2->get_children().back().get();
    variableNode2->add_child(new ObjectToken("Cube"));
    ParseNode* cubeNode = variableNode2->get_children().back().get();
    cubeNode->add_child(new VariableToken{"centroidPoint"});
    cubeNode->add_child(new ArgumentToken{"1"});
    cubeNode->add_child(new ArgumentToken{"1"});
    cubeNode->add_child(new ArgumentToken{"1"});

    ASSERT_EQ(expectedParseTree1, parseTrees[0]);
    std::cout << "Expected:\n" << expectedParseTree1.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[0].to_string() << std::endl;
    ASSERT_EQ(expectedParseTree2, parseTrees[1]);
    std::cout << "Expected:\n" << expectedParseTree2.to_string() << std::endl;
    std::cout << "Actual:\n" << parseTrees[1].to_string() << std::endl;
}