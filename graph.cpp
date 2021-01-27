#include "graph.hpp"

UnweightedGraph::UnweightedGraph(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		throw std::runtime_error{FAILED_OPEN_MSG};
	}
	file>>UnweightedGraph::num_vertices;
	UnweightedGraph::adj_list.resize(num_vertices);
	UnweightedGraph::adj_matrix.resize(num_vertices);
	for (int i=0; i<num_vertices; i++)
	{
		int j=0;
		while (j<num_vertices)
		{
			UnweightedGraph::adj_matrix[i].push_back(0);
			j = j + 1;
		}
	}
	int int_1, int_2;
	//while (file.good())
	while(file>>int_1>>int_2)
	{
		//file>>int_1>>int_2;
		if (int_1 < 0 || int_2 < 0 || int_1 > (UnweightedGraph::num_vertices-1) || int_2 > (UnweightedGraph::num_vertices - 1) || int_1 == int_2)
		{
			throw std::runtime_error{INVALID_GRAPH_MSG};
		}
		if (!(std::count(UnweightedGraph::adj_list[int_1].begin(), UnweightedGraph::adj_list[int_1].end(), int_2)))
		{
			UnweightedGraph::adj_list[int_1].push_back(int_2);
		}
		UnweightedGraph::adj_matrix[int_1][int_2] = 1;
	}
}

int UnweightedGraph::getNumVertices() const
{
    return UnweightedGraph::num_vertices;
}

std::vector<std::vector<bool>> UnweightedGraph::getAdjacencyMatrix() const
{
    return UnweightedGraph::adj_matrix;
}

std::vector<std::vector<int>> UnweightedGraph::getAdjacencyLists() const
{
    return UnweightedGraph::adj_list;
}

std::vector<int> UnweightedGraph::getBFSOrdering(int start) const
{	
	if (start > UnweightedGraph::num_vertices || start < 0)
	{
		return std::vector<int>();
	}
	//make boolean list of what has been seen 
	std::vector<bool> seen;
       	seen.resize(UnweightedGraph::num_vertices);
	for (int i=0; i<UnweightedGraph::num_vertices; i++)
	{
		seen[i] = false;
	}
	//make the queue
	std::queue<int> q;
	//put start on queue and mark as visited
	seen[start] = true;
	q.push(start);
	// make a vector to iterate through all items adjacent to top of queue
	std::vector<int> BFS;
	//iterate through until nothing left on queue
	while (q.size() > 0)
	{
		int current = q.front();
		BFS.push_back(current);
		q.pop(); 
		// for each neighbor n of current node
		for (unsigned int i=0; i< UnweightedGraph::adj_list[current].size(); i++)
		{
			//if seen[n] = false
			if (seen[adj_list[current][i]] == false)
			{
				// seen[n] = true
				seen[adj_list[current][i]] = true;
				// enque n
				q.push(adj_list[current][i]);
			}
		}
	}
	return BFS;
}

std::vector<int> UnweightedGraph::getDFSOrdering(int start) const
{
	if (start > UnweightedGraph::num_vertices || start < 0)
	{
		return std::vector<int>();
	}
	//make boolean list of what has been seen 
	std::vector<bool> seen;
       	seen.resize(UnweightedGraph::num_vertices);
	for (int i=0; i<UnweightedGraph::num_vertices; i++)
	{
		seen[i] = false;
	}
	//make a stack and put start on 
	std::stack<int> s;
	s.push(start);
	std::vector<int> DFS;
	//while stack not empty
	while (s.size() > 0)
	{
		int current = s.top();
		s.pop();
		// if processed[curr_node] is false:
		if (seen[current] == false)
		{
			seen[current] = true; // set to true
			DFS.push_back(current);  // process current
			// for each neighbor n of current node
			for (unsigned int i=0; i< UnweightedGraph::adj_list[current].size(); i++)
			{
				//if seen[n] = false
				if (seen[adj_list[current][i]] == false)
				{
					// push n
					s.push(adj_list[current][i]);
				}
			}
		}
	}
	return DFS;
}

std::vector<std::vector<bool>> UnweightedGraph::getTransitiveClosure() const
{
	std::vector<std::vector<bool>> transitive;
	transitive.resize(UnweightedGraph::num_vertices);
	for (int i=0; i<num_vertices; i++)
	{
		int j=0;
		while (j<num_vertices)
		{
			transitive[i].push_back(0);
			j = j + 1;
		}
	}
	// copy adj_matrix to transitive graph
	for (int i=0; i<UnweightedGraph::num_vertices; i++)
	{
		for (int j=0; j<UnweightedGraph::num_vertices; j++)
		{
			transitive[i][j] = UnweightedGraph::adj_matrix[i][j];
			if (i==j)
			{
				transitive[i][j] = true;
			}
		}
	}
	for (int i=0; i<UnweightedGraph::num_vertices; i++)
	{
		for (int j=0; j<UnweightedGraph::num_vertices; j++)
		{
			for (int k=0; k<UnweightedGraph::num_vertices; k++)
			{
				// if i is on the path from j to k, set to 1
				if (transitive[j][i] == true && transitive[i][k] == true)
				{
					transitive[j][k] = true;
				}
			}
		}
	}
    	return transitive;
}
