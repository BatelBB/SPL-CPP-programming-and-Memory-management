#include <vector>

#include "Graph.h"



using json = nlohmann::json;



//constructor

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infected(std::vector<bool>(matrix.size(), false)) {}



//infects the current node

void Graph::infectNode(int nodeInd) {

    infected[nodeInd] = true;

}



//checks if the current node is infected, returns the value of the infected vector

bool Graph::isInfected(int nodeInd) {

    return infected[nodeInd];

}



//getter - returns the vector of the neighbors of the node.

std::vector<int> Graph::getNodeNeighbors(int nodeInd) const {

    std::vector<int> nodeNeighbors;



    int edgesSize = edges.size();  //it's for the unsigned integer

    for (int i = 0; i < edgesSize; i++) {

        if (edges[nodeInd][i] == 1) {

            nodeNeighbors.push_back(i);

        }

    }

    return nodeNeighbors;

}



//takes the infected node and cuts the edges from it, separates it from the graph

void Graph::separateNode(int nodeInd) {

    int edgesSize = edges.size(); //it's for the unsigned integer

    for (int i = 0; i < edgesSize; i++) {

        edges[nodeInd][i] = 0;

        edges[i][nodeInd] = 0;

    }

}



//takes the data and puts it in the json file, used the github repo to handle the writing

json Graph::writejson() {

    json js;

    js["graph"] = edges;



    std::vector<int> currInfected;



    int infectedSize = infected.size();//to deal with unsigned integer

    for (int i = 0; i < infectedSize; i++) {

        if (infected[i]) {

            currInfected.push_back(i);

        }

    }



    js["infected"] = currInfected;



    return js;

}



//runs the BFS algorithim

Tree *Graph::BFS(int nodeInd, const Session &session) const {



    Tree *root = Tree::createTree(session, nodeInd);



    std::queue<Tree *> BFSQ;

    std::vector<bool> isVisited(edges.size(), false);

    std::vector<int> nodeNeighbors = getNodeNeighbors(nodeInd);



    isVisited[nodeInd] = true;

    BFSQ.push(root);



    while (!BFSQ.empty()) {



        Tree *currTree = BFSQ.front();

        int currNode;

        int subTrees = 0;



        BFSQ.pop();

        currNode = currTree->getNode();

        nodeNeighbors = getNodeNeighbors(currNode);





        int nodeNeighborsSize = nodeNeighbors.size(); //to deal with unsigned integer

        for (int i = 0; i < nodeNeighborsSize; i++) {



            if (!isVisited[nodeNeighbors[i]]) {

                Tree *child = Tree::createTree(session, nodeNeighbors[i]);

                isVisited[nodeNeighbors[i]] = true;



                currTree->addChild(*child);

                BFSQ.push(currTree->getSubTrees()[subTrees]);

                subTrees++;



                delete child;

            }

        }

    }



    return root;

}

