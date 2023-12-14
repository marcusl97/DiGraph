#include <iostream>
#include <vector>


class DiGraph;

// Structure for a node in the graph
struct Node {
    std::string name;
    std::vector<Node> neighbours;
    bool seen;

    // Constructor with a name parameter
    explicit Node(std::string nodeName) : name(std::move(nodeName)), seen(false) {}

    bool operator==(const Node& other) const {
        return name == other.name;
    }

};

// Class representing a directed graph
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
    static bool graph_node_is_seen(const Node& n);
    static void graph_node_set_seen(Node& n, bool seen);
    void graph_reset_seen();
    void graph_print() const;
    std::vector<Node*> node_neighbours(Node& n);

private:
    std::vector<Node> m_nodes;
    int m_numEdges = 0;
};

bool DiGraph::nodes_are_equal(const Node& n1, const Node& n2) {
    return n1 == n2;
}

bool DiGraph::graph_is_empty() {
    return m_nodes.empty();
}

bool DiGraph::graph_has_edges() {
    return m_numEdges > 0;
}

void DiGraph::graph_insert_node(std::string name) {
    m_nodes.emplace_back(std::move(name));
}

Node* DiGraph::graph_find_node(const std::string name) {
    for (auto & m_node : m_nodes) {
        if (m_node.name == name) {
            return &m_node;  // Return a pointer to the found node.
        }
    }

    return nullptr;
}

void DiGraph::graph_delete_node(Node& n) {
    // Delete all edges to the node
    for (auto& node : m_nodes) {
        graph_delete_edge(node, n);
    }

    // Remove the node from the graph
    m_nodes.erase(std::remove_if(m_nodes.begin(), m_nodes.end(),
                                 [this, &n](const auto& current) { return nodes_are_equal(current, n); }),
                  m_nodes.end());

}

void DiGraph::graph_delete_edge(Node& n1, Node& n2)
{
    auto neighbor_it = std::remove_if(n1.neighbours.begin(), n1.neighbours.end(),
                                      [this, &n2](const auto& neighbour) { return nodes_are_equal(neighbour, n2); });

    n1.neighbours.erase(neighbor_it, n1.neighbours.end());
    m_numEdges--;
}

bool DiGraph::graph_node_is_seen(const Node& n) {
    return n.seen;
}

void DiGraph::graph_node_set_seen(Node& n, bool seen) {
    n.seen = seen;
}

void DiGraph::graph_reset_seen() {
    for (auto& node : m_nodes) {
        node.seen = false;
    }
}

void DiGraph::graph_insert_edge(Node* n1, Node* n2) {
    if (n1 && n2) {
        n1->neighbours.push_back(*n2);
        m_numEdges++;
    }
}

std::vector<Node*> DiGraph::node_neighbours(Node& n)
{
    std::vector<Node*> neighbours;
    for (Node& node : n.neighbours) {
        neighbours.push_back(&node);
    }
    return neighbours;
}

void DiGraph::graph_print() const {
    for (const auto& n : m_nodes) {
        std::cout << "Node: " << n.name << ", Seen: " << (n.seen ? "true" : "false") << ", Neighbors: [";
        for (const auto& neighbour : n.neighbours) {
            std::cout << neighbour.name << ", ";
        }
        std::cout << "]" << std::endl;
    }
}