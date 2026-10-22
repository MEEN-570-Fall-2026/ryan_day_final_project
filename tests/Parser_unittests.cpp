#include "gtest/gtest.h"
#include "Parser.hpp"
#include <string>
#include "ParseNode.hpp"
#include "ParseToken.hpp"
#include "ParseTree.hpp"
#include <format>

ParseTree constructTreeWithHead()
{
    ParseToken headToken = ParseToken("HeadToken");
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    return ParseTree(headNode);
}


ParseNode* addIterativeRightChildren(ParseTree& tree, int childrenLayers)
{
    ParseNode* head = tree.get_head_node();
    ParseToken rightToken{"RightToken0"};
    head->add_child(rightToken);
    ParseNode* rightChildNode = head->get_children().back().get();
    for (int i = 1; i < childrenLayers; i++)
    {
        ParseToken leafTokenRight = ParseToken(std::format("Leaf{}", i));
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
    ParseToken headToken = ParseToken("HeadToken");
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseToken child1Token = ParseToken("child1");
    ParseToken child2Token = ParseToken("child2");
    headNode->add_child(child1Token);
    headNode->add_child(child2Token);
    const auto& children = headNode->get_children();
    ASSERT_EQ(children.size(), 2);
    ASSERT_EQ(children[0]->get_value().getTokenText(), child1Token.getTokenText());
    ASSERT_EQ(children[1]->get_value().getTokenText(), child2Token.getTokenText());
}

TEST(ParseTree, GivenAParseTree_WhenAddingNewNodes_ExpectLeavesUpdate)
{
    ParseTree tree = constructTreeWithHead();
    ParseNode* head = tree.get_head_node();
    ParseToken leafToken1 = ParseToken("Leaf1");
    ParseToken leafToken2 = ParseToken("Leaf2");
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
    ParseToken leafTokenLeft = ParseToken("LeafLeft");
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
    ParseToken token1{"Value"};
    ParseToken token2{"Value"};
    ASSERT_EQ(token1, token2);
}


TEST(ParseNode, GivenTwoEqualParseNodes_WhenCheckingNodeEquality_ExpectNodesEqual)
{
    ParseNode node1{ParseToken{"Value"}, nullptr};
    ParseNode node2{ParseToken{"Value"}, nullptr};
    ASSERT_EQ(node1, node2);
}


TEST(ParseNode, GivenTwoParseNodesWithDifferentChildren_WhenCheckingNodeEquality_ExpectNodesUnequal)
{
    ParseNode node1{ParseToken{"Value"}, nullptr};
    ParseNode node2{ParseToken{"Value"}, nullptr};
    node2.add_child(ParseToken("Child"));
    ASSERT_NE(node1, node2);
}


TEST(ParseNode, GivenTwoParseNodesWithSameChildren_WhenCheckingNodeEquality_ExpectNodesEqual)
{
    ParseNode node1{ParseToken{"Value"}, nullptr};
    ParseNode node2{ParseToken{"Value"}, nullptr};
    node2.add_child(ParseToken("Child"));
    node1.add_child(ParseToken("Child"));
    ASSERT_EQ(node1, node2);
}


TEST(Parser, GivenASimpleInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(1,1,1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken headToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(ParseToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenANestedInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(Point(1,2,3),1,1,1);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken headToken{"StatementStart"};
    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree{headNode};
    headNode->add_child(ParseToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(ParseToken("Point"));
    ParseNode* pointToken = cubeToken->get_children().back().get();
    pointToken->add_child(ParseToken{"1"});
    pointToken->add_child(ParseToken{"2"});
    pointToken->add_child(ParseToken{"3"});
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});
    ASSERT_EQ(expectedParseTree, parseTrees[0]);
}

TEST(Parser, GivenAMultiLineArgumentInputString_WhenParsingInput_ExpectCorrectParseTreeCreated)
{
    std::string input = "Cube(Point(1,2,3),1,1,1);\nPoint(1,1,1);\nCube(1,2,3);";
    Parser parser;
    std::vector<ParseTree> parseTrees = parser.parse_from_string(input);
    ParseToken headToken{"StatementStart"};

    ParseNode* headNode = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree1{headNode};
    headNode->add_child(ParseToken{"Cube"});
    ParseNode* cubeToken = headNode->get_children().back().get();
    cubeToken->add_child(ParseToken("Point"));
    ParseNode* pointToken = cubeToken->get_children().back().get();
    pointToken->add_child(ParseToken{"1"});
    pointToken->add_child(ParseToken{"2"});
    pointToken->add_child(ParseToken{"3"});
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});
    cubeToken->add_child(ParseToken{"1"});

    ParseNode* headNode2 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree2{headNode2};
    headNode2->add_child(ParseToken{"Point"});
    ParseNode* pointToken2 = headNode2->get_children().back().get();
    pointToken2->add_child(ParseToken{"1"});
    pointToken2->add_child(ParseToken{"1"});
    pointToken2->add_child(ParseToken{"1"});

    ParseNode* headNode3 = new ParseNode(headToken, nullptr);
    ParseTree expectedParseTree3{headNode3};
    headNode3->add_child(ParseToken{"Cube"});
    ParseNode* cubeToken3 = headNode3->get_children().back().get();
    cubeToken3->add_child(ParseToken{"1"});
    cubeToken3->add_child(ParseToken{"2"});
    cubeToken3->add_child(ParseToken{"3"});

    ASSERT_EQ(expectedParseTree1, parseTrees[0]);
    ASSERT_EQ(expectedParseTree2, parseTrees[1]);
    ASSERT_EQ(expectedParseTree3, parseTrees[2]);
}