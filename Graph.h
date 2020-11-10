#ifndef GRAPH_H_
	#define GRAPH_H_
	

	#include <vector>
	

	class Graph{
	public:
	    // need default constructor for session constructor, as meni said in lecture 6 when someone asked
	    Graph();
	

	    Graph(std::vector<std::vector<int>> matrix); 
	    
	    void infectNode(int nodeInd);
	    bool isInfected(int nodeInd);
	

	    //getNeighbors should return a sorted list of node ids that are adjacent to nodeInd
	    std::vector<int> getNeighbours(int nodeInd) const;
	

	    // isolate should remove all links to adjacent nodes to the given node
	    void isolate(int nodeInd);
	

	    int size() const;
	

	    std::vector<std::vector<int>> getEdges() const;
	    std::vector<int> getInfected() const; 
	

	private:
	    std::vector<std::vector<int>> edges;
	    std::vector<bool> infected;
	};
	

	#endif

