#ifndef GRAPH_H_

#define GRAPH_H_





#include <vector>

#include "json.hpp"

#include "Tree.h"

#include <queue>



class Graph {

public:

    Graph(std::vector<std::vector<int>> matrix);



    void infectNode(int nodeInd);



    bool isInfected(int nodeInd);



    std::vector<int> getNodeNeighbors(int nodeInd) const;



    void separateNode(int nodeInd);



    nlohmann::json writejson();



    Tree *BFS(int nodeInd, const Session &session) const;



private:

    std::vector<std::vector<int>> edges;





    std::vector<bool> infected;

};



#endif

