#ifndef SESSION_H_
#define SESSION_H_


#include <vector>
#include <string>
#include "Graph.h"
#include "Tree.h"
#include "json.hpp"
#include <queue>


class Agent;


enum TreeType {
    Cycle,
    MaxRank,
    Root
};


class Session {
public:
    Session(const std::string &path);

    ~Session();

    Session(const Session &other);

    Session &operator=(const Session &other);

    Session(Session &&other);

    Session &operator=(Session &&other);


    void writejson(const std::string &path);

    void readjson(const nlohmann::json &j);

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    void enqueueInfected(int);

    int dequeueInfected();

    TreeType getTreeType() const;


    int getCurrCycle() const;

    bool isCarrierAt(int nodeInd) const;


    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    std::vector<int> getNodeNeighbors(int nodeInd) const;

    void separateNode(int nodeInd);

    Tree *BFS(int nodeInd) const;


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;

    std::vector<bool> isVirusCarrier;
    std::queue<int> infectedQueue;

    int currCycle;

    void clear();

    void copy(const Graph &otherGraph, const TreeType otherTreeType, const std::vector<Agent *> &otherAgents,
              const std::vector<bool> &otherViCar, const std::queue<int> &otherInfeQ, const int otherCycle);
};


#endif

