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