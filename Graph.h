#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    //it gets a matrix that is a vector of vectors of type int, I think we supposed to create a graph out of it
    Graph(std::vector<std::vector<int>> matrix);
    
    //represents the infectedNode in the current cycle in the graph
    void infectNode(int nodeInd);

    //boolean method that checks if the current node is infected or not
    bool isInfected(int nodeInd);
private:

    //the edges of the graph, not sure what to do with that
    std::vector<std::vector<int>> edges;
};

#endif
