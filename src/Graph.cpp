#include <vector>
#include "Graph.h"


using json = nlohmann::json;

//constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infected(std::vector<int>()) {}

//infects the current node
void Graph::infectNode(int nodeInd) {
    infected.push_back(nodeInd);
}

//checks if the current node is infected, returns true if it's infected or false if it's not
bool Graph::isInfected(int nodeInd) {
    int infectedVecSize = infected.size();
    for (int i = 0; i < infectedVecSize; i++) {
        if (infected[i] == nodeInd) {
            return true;
        }
    }
    return false;
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
    js["infected"] = infected;

    return js;
}

Tree *Graph::BFSRecur(std::queue<Tree *> BFSR, const Session &session, std::vector<bool> isVisited) const {
    //creates a new tree pointer and points to the first element of the tree queue
    Tree *currTree = BFSR.front();
    //takes out the first element of the queue
    BFSR.pop();

    //sets the current tree's root
    int currNode = currTree->getNode();
    //int vector that saves the current node neighbors
    std::vector<int> nodeNeighbors = getNodeNeighbors(currNode);
    //counts the number of subtrees of the current node
    int subTrees = 0;

    int nodeNeighborsSize = nodeNeighbors.size(); //to deal with unsigned integer
    //runs in a loop on the neighbors
    for (int i = 0; i < nodeNeighborsSize; i++) {
        //checks if the node have been visited
        if (!isVisited[nodeNeighbors[i]]) {
            //creates a pointer to the current sub trees
            Tree *currSubTree = Tree::createTree(session, nodeNeighbors[i]);
            //marks the subtree as visited
            isVisited[nodeNeighbors[i]] = true;

            //adds a pointer of the current sub tree as a child of the current tree
            currTree->addChild(*currSubTree);
            //adds the current sub tree to the queue
            BFSR.push(currTree->getSubTrees()[subTrees]);
            subTrees++;

            delete currSubTree;
        }
    }
    //if the queue isn't empty, calls recursively to the BFSRecur
    if (!BFSR.empty())

        return BFSRecur(BFSR, session, isVisited);

    //once the BFSR is empty returns the current tree
    return currTree;

}

//runs the BFS algorithm
Tree *Graph::BFS(int nodeInd, const Session &session) const {
    Tree *root = Tree::createTree(session, nodeInd);
    std::vector<bool> isVisited(edges.size(), false);
    std::queue<Tree *> BFSQ;
    isVisited[nodeInd] = true;
    BFSQ.push(root);

    //recursive call
    this->BFSRecur(BFSQ, session, isVisited);

    return root;
}

