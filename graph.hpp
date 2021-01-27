#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>
#include <algorithm>

#define FAILED_OPEN_MSG "Failed to open file"
#define INVALID_GRAPH_MSG "Invalid graph"

class UnweightedGraph
{

public:
    UnweightedGraph(const std::string& filename);
    int getNumVertices() const;
    std::vector<std::vector<bool>> getAdjacencyMatrix() const;
    std::vector<std::vector<int>> getAdjacencyLists() const;
    std::vector<int> getBFSOrdering(int start) const;
    std::vector<int> getDFSOrdering(int start) const;
    std::vector<std::vector<bool>> getTransitiveClosure() const;

private:
	int num_vertices;
	std::vector<std::vector<int>> adj_list;
	std::vector<std::vector<bool>> adj_matrix;
};

#endif // GRAPH_HPP
