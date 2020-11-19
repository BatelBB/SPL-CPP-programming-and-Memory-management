#include <vector>
#include "Graph.h"

using json = nlohmann::json;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infected(std::vector<bool>(matrix.size(), false)) {}

void Graph::infectNode(int nodeInd) {
    infected[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd];
}

std::vector<int> Graph::getNodeNeighbors(int nodeInd) const {
    std::vector<int> nodeNeighbors;
    int edgesSize = edges.size();  //Batel - it's for the unsigned integer
    for (int i = 0; i < edgesSize; i++) {
        if (edges[nodeInd][i] == 1) {
            nodeNeighbors.push_back(i);
        }
    }

    return nodeNeighbors;
}


void Graph::separateNode(int nodeInd) {
    int edgesSize = edges.size(); //Batel - it's for the unsigned integer
    for (int i = 0; i < edgesSize; i++) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

json Graph::writejson() {
    json js;

    std::vector<int> currInfected;
    int infectedSize = infected.size();
    for (int i = 0; i < infectedSize; i++) {
        if (infected[i]) {
            currInfected.push_back(i);
        }
    }

    js["graph"] = edges;
    js["infected"] = currInfected;


    return js;
}

Tree *Graph::BFS(int nodeInd, const Session &session) const {
    std::vector<int> neighbours = getNodeNeighbors(nodeInd);


    std::vector<bool> visited(edges.size(), false);

    std::queue<Tree *> BFSqueue;

    Tree *root = Tree::createTree(session, nodeInd);

    visited[nodeInd] = true;
    BFSqueue.push(root);

    while (!BFSqueue.empty()) {

        Tree *currTree = BFSqueue.front();
        int currNode = currTree->getNode();
        BFSqueue.pop();

        neighbours = getNodeNeighbors(currNode);

        int subTreesNum = 0;
        int neighboursSize = neighbours.size();
        for (int i = 0; i < neighboursSize; i++) {

            if (!visited[neighbours[i]]) {
                Tree *child = Tree::createTree(session, neighbours[i]);
                visited[neighbours[i]] = true;

                currTree->addChild(*child);
                BFSqueue.push(currTree->getSubTrees()[subTreesNum]);
                subTreesNum++;

                delete child;
            }
        }
    }

    return root;
}

