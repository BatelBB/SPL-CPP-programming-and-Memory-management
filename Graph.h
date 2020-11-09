#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph
{
public:
    //default constructor
    Graph();

    //constructor, initilizing with edges and "isInfectedVec" - to get a graph that's initilized from zero.
    Graph(std::vector<std::vector<int>> matrix);

    //it take the current node and puts the virus in it. (bool - turns it to true)
    void infectNode(int nodeInd);

    //boolean method that checks if the current node is infected or not (calls the isInfectedVec with the curr nodeInd)
    bool isInfected(int nodeInd);

    //uses a queue data structure to handle the neighbors of the node,
    //take a one dimention int vector and pushes it every time there's an edge between two nodes.
    std::vector<int> getNodeNeighbors(int nodeInd) const;

    //takes the node that has been infected and removes it from the graph, separeting it from it fellow nodes.
    //using the edges 2 dimention vector - deleting the edges (0).
    void remove(int nodeInd);

    //returns the number of edges in the 2 dimention vector edges.
    int graphSize() const;

    std::vector<std::vector<int>> getGraph() const;

    std::vector<int> getInfectedNodes() const;

private:
    //the edges of the graph
    std::vector<std::vector<int>> edges;

    //a boolean vector array that contains the infection information of each node.
    std::vector<bool> isInfectedVec;
};

#endif
