//
// Created by marcuslundqvist on 2023-12-14.

#include "gtest/gtest.h"
#include "../graph.h"

// Define test fixtures if needed
class GraphTest : public ::testing::Test {
protected:
    // Set up common conditions for test cases
    void SetUp() override {
        // Initialize common resources
    }

    // Clean up after test cases
    void TearDown() override {
        // Release resources
    }

    DiGraph graph;
};

// Define your test cases
TEST_F(GraphTest, GraphIsEmptyInitially) {
    EXPECT_TRUE(graph.graph_is_empty());
    EXPECT_FALSE(graph.graph_has_edges());
}

TEST_F(GraphTest, GraphInsertNode) {
    graph.graph_insert_node("A");
    EXPECT_FALSE(graph.graph_is_empty());
    EXPECT_FALSE(graph.graph_has_edges());
}

TEST_F(GraphTest, GraphFindNode) {
    graph.graph_insert_node("A");
    Node *n = graph.graph_find_node("A");
    EXPECT_NE(n, nullptr);
    EXPECT_EQ(n->name, "A");
    n = graph.graph_find_node("B");
    EXPECT_EQ(n, nullptr);

}

TEST_F(GraphTest, GraphTestSeenFalse) {
    graph.graph_insert_node("A");
    EXPECT_FALSE(graph.graph_node_is_seen(*graph.graph_find_node("A")));
}

TEST_F(GraphTest, GraphTestSetSeen) {
    graph.graph_insert_node("A");
    Node *n = graph.graph_find_node("A");
    graph.graph_node_set_seen(*n, true);
    EXPECT_TRUE(graph.graph_node_is_seen(*n));
    graph.graph_node_set_seen(*n, false);
    EXPECT_FALSE(graph.graph_node_is_seen(*n));
}

TEST_F(GraphTest, NodesAreEqual) {
    EXPECT_TRUE(graph.nodes_are_equal(Node("A"), Node("A")));
}

TEST_F(GraphTest, GraphInsertEdge) {
    graph.graph_insert_node("A");
    graph.graph_insert_node("B");
    graph.graph_insert_edge(graph.graph_find_node("A"), graph.graph_find_node("B"));
    EXPECT_TRUE(graph.graph_has_edges());
}

TEST_F(GraphTest, GraphDeleteNode) {
    graph.graph_insert_node("A");
    graph.graph_insert_node("B");
    graph.graph_insert_edge(graph.graph_find_node("A"), graph.graph_find_node("B"));
    graph.graph_delete_node(*graph.graph_find_node("A"));
    EXPECT_FALSE(graph.graph_is_empty());
    EXPECT_FALSE(graph.graph_has_edges());
    graph.graph_delete_node(*graph.graph_find_node("B"));
    EXPECT_TRUE(graph.graph_is_empty());
}

TEST_F(GraphTest, GraphDeleteEdge) {
    graph.graph_insert_node("A");
    graph.graph_insert_node("B");
    graph.graph_insert_edge(graph.graph_find_node("A"), graph.graph_find_node("B"));
    graph.graph_delete_edge(*graph.graph_find_node("A"), *graph.graph_find_node("B"));
    EXPECT_FALSE(graph.graph_has_edges());
}

TEST_F(GraphTest, GraphResetSeen) {
    graph.graph_insert_node("A");
    graph.graph_insert_node("B");
    graph.graph_node_set_seen(*graph.graph_find_node("A"), true);
    graph.graph_node_set_seen(*graph.graph_find_node("B"), true);
    graph.graph_reset_seen();
    EXPECT_FALSE(graph.graph_node_is_seen(*graph.graph_find_node("A")));
    EXPECT_FALSE(graph.graph_node_is_seen(*graph.graph_find_node("B")));
}

// Add more test cases as needed

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
