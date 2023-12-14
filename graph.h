#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>
#include <vector>
#include <memory>

struct Node {
    std::string name;
    std::vector<Node> neighbours;
    bool seen;

    explicit Node(std::string nodeName);
};

class DiGraph {
public:
    bool nodes_are_equal(const Node& n1, const Node& n2);
    bool graph_is_empty();
    bool graph_has_edges();
    void graph_insert_node(std::string name);
    Node* graph_find_node(std::string name);
    void graph_delete_node(Node& n);
    void graph_insert_edge(Node* n1, Node* n2);
    void graph_delete_edge(Node& n1, Node& n2);
    bool graph_node_is_seen(const Node& n);
    void graph_node_set_seen(Node& n, bool seen);
    void graph_reset_seen();
    void graph_print() const;
    std::vector<Node*> node_neighbours(Node& n);

private:
    std::vector<Node> m_nodes;
    int m_numEdges = 0;
};

#endif //DIGRAPH_H