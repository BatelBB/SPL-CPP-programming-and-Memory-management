#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Session.h"
#include "Agent.h"
#include "json.hpp"


using json = nlohmann::json;

//constructor
Session::Session(const std::string &path) : g(Graph(std::vector<std::vector<int>>())), treeType(Root),
                                            agents(std::vector<Agent *>()), isVirusCarrier(std::vector<bool>()),
                                            infectedQueue(std::queue<int>()), currCycle(0) {

    //Open json file
    std::ifstream inputFile;
    inputFile.open(path);
    json js;
    inputFile >> js;
    readjson(js);
}

//Destructor
Session::~Session() {
    clear();
}

//clear method for destructor
void Session::clear() {
    for (Agent *agent : agents)
        if (agent) {
            delete agent;
        }
    agents.clear();
}

//copy constructor
Session::Session(const Session &other) : g(Graph(std::vector<std::vector<int>>())), treeType(Root),
                                         agents(std::vector<Agent *>()), isVirusCarrier(std::vector<bool>()),
                                         infectedQueue(std::queue<int>()), currCycle(0) {

    copy(other.g, other.treeType, other.agents, other.isVirusCarrier, other.infectedQueue, other.currCycle);
}

//copy constructor
void Session::copy(const Graph &otherGraph, const TreeType otherTreeType, const std::vector<Agent *> &otherAgents,
                   const std::vector<bool> &otherViCar, const std::queue<int> &otherInfeQ, const int otherCycle) {
    g = otherGraph;
    treeType = otherTreeType;
    currCycle = otherCycle;
    infectedQueue = otherInfeQ;
    isVirusCarrier = otherViCar;
    for (auto &agent : otherAgents) {
        addAgent(*agent);
    }
}

//copy assignment operator
Session &Session::operator=(const Session &other) {

    if (this != &other) {
        clear();
        copy(other.g, other.treeType, other.agents, other.isVirusCarrier, other.infectedQueue, other.currCycle);
    }
    return *this;
}

//move constructor
Session::Session(Session &&other) : g(std::move(other.g)), treeType(other.treeType), agents(move(other.agents)),
                                    isVirusCarrier(std::move(other.isVirusCarrier)),
                                    infectedQueue(std::move(other.infectedQueue)), currCycle(other.currCycle) {
    other.treeType = Root;
    other.currCycle = 0;
}

//move assignment operator
Session &Session::operator=(Session &&other) {

    if (this != &other) {

        g = std::move(other.g);
        treeType = other.treeType;
        agents = std::move(other.agents);
        isVirusCarrier = std::move(other.isVirusCarrier);
        infectedQueue = std::move(other.infectedQueue);
        currCycle = other.currCycle;
        other.treeType = Root;
        other.currCycle = 0;
    }

    return *this;
}


//creat an output json file
void Session::writejson(const std::string &path) {

    json js = g.writejson();
    std::ofstream outputFile;
    outputFile.open(path);
    outputFile << js << std::endl;
}

//Read the json file
void Session::readjson(const json &js) {

    std::vector<std::vector<int>> matrix;
    js.at("graph").get_to(matrix);
    g = Graph(matrix);
    isVirusCarrier = std::vector<bool>(matrix[0].size(),false);
    std::string treeLetter = js["tree"];

    for (auto &element : js.at("agents")) {
        std::string agentType = element[0];
        int nodeInd = element[1];
        if (agentType == "V") {
            addAgent(Virus(nodeInd));
        } else {
            addAgent(ContactTracer());
        }
    }

    //get the tree type
    if (treeLetter == "M") {
        treeType = MaxRank;
    } else if (treeLetter == "C") {
        treeType = Cycle;
    } else {
        treeType = Root;
    }
}

//runs the simulator
void Session::simulate() {
    std::string outputPath = "./output.json";
    bool Spreading = true;

    while (Spreading) {
        int agentsSize = agents.size(); //to deal with unsigned integer
        for (int i = 0; i < agentsSize; i++) {
            agents[i]->act(*this);
        }

        Spreading = false;
        int isVirusCarrierSize = isVirusCarrier.size(); //to deal with unsigned integer
        for (int i = 0; i < isVirusCarrierSize; i++) {
            if (isCarrierAt(i) != isInfected(i)) {
                Spreading = true;
            }
        }
        currCycle++;
    }
    writejson(outputPath);
}

//adds a new agent using the clone method, checks if it's a virus and if not and supposed to be then sets it to true.
void Session::addAgent(const Agent &agent) {
    //takes the agent and pushes the clone to the agents vector
    agents.push_back(agent.clone());
    //if it's not contact tracer then it's a virus carrier
    if (agent.getNodeInd() != -1) {
        isVirusCarrier[agent.getNodeInd()] = true;
   }
}

//sets g to be the graph
void Session::setGraph(const Graph &graph) {
    g = graph;
}

//pushes the infected nodes to the queue
void Session::enqueueInfected(int nodeInd) {
    infectedQueue.push(nodeInd);
}

//checks if there is something in queue and if there is then it pops out the first node.
int Session::dequeueInfected() {
    if (getQSize() != 0) {
        int topNode = infectedQueue.front();
        infectedQueue.pop();
        return topNode;
    }
    return -1;
}

//getter - tree type
TreeType Session::getTreeType() const {
    return treeType;
}

//getter - current cycle
int Session::getCurrCycle() const {
    return currCycle;
}

//returns if the node have a virus or not.
bool Session::isCarrierAt(int nodeInd) const {
    return isVirusCarrier[nodeInd];
}

//from Graph - infects the node that is given from the graph
void Session::infectNode(int nodeInd) {
    g.infectNode(nodeInd);
}

//returns if the node that is given is infected or not
bool Session::isInfected(int nodeInd) {
    return g.isInfected(nodeInd);
}

//getter - node getter
std::vector<int> Session::getNodeNeighbors(int nodeInd) const {
    return g.getNodeNeighbors(nodeInd);
}

//getter - returns the size of the queue
int Session::getQSize() const {
    return infectedQueue.size();
}

//a method to separate the node, to be used by the contact tracer
void Session::separateNode(int nodeInd) {
    g.separateNode(nodeInd);
}

//returns a tree for the BFS method
Tree *Session::BFS(int nodeInd) const {
    return g.BFS(nodeInd, *this);
}

