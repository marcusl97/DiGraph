#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include "graph.h"

std::ifstream openFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << '\n';
        // You might want to handle the failure differently, e.g., throw an exception
        // or return a special value indicating the failure.
    }
    return std::move(file);
}

void insertAirlines(DiGraph& g, const std::string& node_name, const std::string& neighbor_name)
{
    auto n1 = g.graph_find_node(node_name);
    auto n2 = g.graph_find_node(neighbor_name);
    if (!g.graph_is_empty())
    {
        if (n1 == nullptr)
        {
            g.graph_insert_node(node_name);
        }


        if (n2 == nullptr)
        {
            g.graph_insert_node(neighbor_name);
        }

        g.graph_insert_edge(g.graph_find_node(node_name), g.graph_find_node(neighbor_name)); // Dereference the shared pointers
    }
    else
    {
        g.graph_insert_node(node_name);
        g.graph_insert_node(neighbor_name);
        g.graph_insert_edge(g.graph_find_node(node_name), g.graph_find_node(neighbor_name)); // Dereference the shared pointers
    }

}

void parseInput(std::ifstream file, DiGraph& g)  // Pass by value (move semantics)
{
    std::string line;
    int value = -1;
    std::string nodeName1;
    std::string nodeName2;

    while (std::getline(file, line))
    {
        // Skip empty lines or lines starting with '#'
        if (line.empty() || line.at(0) == '#')  {
            continue;
        }

        std::istringstream ss(line);
        std::cout << "Line: "  << line << '\n';
        if(value == -1)
        {
            while (ss >> value) {
                std::cout << "Num Nodes: " << value << '\n';
            }
            continue;
        }
        else
        {
            ss >> nodeName1;
            ss >> nodeName2;
            std::cout << "Node 1: " << nodeName1 << " Node2: "  << nodeName2 << '\n';
            insertAirlines(g, nodeName1, nodeName2);
        }
    }
}


bool find_path(DiGraph& g, std::string& src_name, std::string& dest_name)
{
    auto src = g.graph_find_node(src_name);
    auto dest = g.graph_find_node(dest_name);

    if (src == nullptr || dest == nullptr)
    {
        std::cerr << "One or both of the places does not exist in the graph\n";
        return false;
    }

    std::cout << "Source Node Name: " << src->name << std::endl;
    std::cout << "Destination Node Name: " << dest->name << std::endl;



    if (g.nodes_are_equal(*src, *dest))
    {
        // The start and target nodes are the same, so there is a trivial path.
        return true;
    }

    // Reset the seen status of all nodes in the graph.
    g.graph_reset_seen();

    // Create a queue to store the nodes to visit.
    std::queue<Node*> q;

    // Enqueue the start node and mark it as seen.
    q.push(src);
    g.graph_node_set_seen(*src, true);

    while (!q.empty())
    {
        // Save the first node and dequeue it.
        Node* current = q.front();
        //std::cout << "Current node: "<< current->name << " Seen: " << (g.graph_node_is_seen(*src) ? "true" : "false") << std::endl;
        q.pop();


        // Check if the current node is the target node.
        if (g.nodes_are_equal(*dest, *current))
        {
            // Found a path from start to target.
            return true;
        }

        // Get the neighbors of the current node.
        std::vector<Node*> neighbors = g.node_neighbours(*current);

        for (Node* node : neighbors)
        {
            if (!g.graph_node_is_seen(*node))
            {
                q.push(node);
                g.graph_node_set_seen(*node, true);
            }
        }
    }

    return false;
}



int main() {
    DiGraph graph;
    // Open map
    std::ifstream inputFile = openFile("input.txt");
    // Parse map
    parseInput(std::move(inputFile), graph);  // Use std::move to pass by value

    std::string start = "BMA";
    std::string dest = "UME";

    bool result = find_path(graph, start, dest);

    std::cout << "There is a path between: " << start << " and: "  << dest << ": " << std::boolalpha << result << '\n';

    graph.graph_print();

    return 0;
}
