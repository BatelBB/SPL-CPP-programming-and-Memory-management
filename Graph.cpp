#include <vector>
	#include "Graph.h"
	

	using namespace std;
	

	// should pass empty vectors or nullptr?
	Graph::Graph(){}
	

	Graph::Graph(vector<vector<int>> matrix): edges(matrix), infected(vector<bool>(matrix[0].size(),false)){}
	

	bool Graph::isInfected(int nodeInd)
	{
	    return infected[nodeInd];
	}
	

	void Graph::infectNode(int nodeInd)
	{
	    infected[nodeInd] = true;
	}
	

	//getNeighbors should return a sorted list of node ids that are adjacent to nodeInd
	vector<int> Graph::getNeighbours(int nodeInd) const
	{
	    vector<int> neighbours;
	

	    for (int i=0; i<edges.size(); i++)
	    {
	        if (edges[nodeInd][i] == 1)
	        {
	            neighbours.push_back(i);
	        }
	    }
	

	    return neighbours;
	}
	

	// isolate should remove all links to adjacent nodes to the given node
	void Graph::isolate(int nodeInd)
	{
	    for (int i=0; i<edges.size(); i++)
	    {
	        edges[nodeInd][i] = 0;
	        edges[i][nodeInd] = 0;
	    }
	}
	

	int Graph::size() const
	{
	    return edges[0].size();
	}
	

	vector<vector<int>> Graph::getEdges() const
	{
	    return edges;
	}
	

	std::vector<int> Graph::getInfected() const
	{
	    vector<int> currentInfected;
	    for (int i=0; i<infected.size(); i++)
	    {
	        if (infected[i])
	        {
	            currentInfected.push_back(i);
	        }
	    }
	

	    return currentInfected;
	}

