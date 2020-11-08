#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "Session.h"
#include "Agent.h"
#include "Graph.h"

using json = nlohmann::json;

//std::ifstream ifs("/home/spl211/Assignment1/Test/config1.json");
//json js = json::parse(ifs);

//Our Method - Dolav Screenshot
//Session::Session(const Session &other) : g(), treeType(other.treeType), agents()
//{
//for (int i = 0; i < other.agents.size(); ++i)
// {
//     Agent *newAgent = other.agents[i].clone();
//     agents.push_back(newAgent);
// }
//}

//the initilization and the mimush is from Dolav video
Session::Session(const std::string &path) : currCycleInd(0)
{
    std::ifstream i(path);
    json js;
    i >> js;

    this->readJson(js);
}

//Session.addAgent(Virus(2));            //We added from the screenshot

//addAgent(const Agent& agent){
//   Agent* clone = agent.clone();      //We added from the screenshot
//}

void simulate()
{
}

void Session::addAgent(const Agent &agent)
{
    agents.push_back(agent.clone());
    int nodeIndex = agent.getNodeIndex();
    if (nodeIndex != -1)
    {
        isCarrier[nodeIndex] = true;
    }
}

//TODO
void setGraph(const Graph &graph)
{
}

void Session::enqueueInfected(int nodeInd)
{
    //push_back vector
    infectedQueue.push(nodeInd);
}
// use vectors to be productive
//takes the object in the 0 spot and deletes it
int Session::dequeueInfected()
{
    if (!infectedQueue.empty())
    {
        int nextNode = infectedQueue.front();
        infectedQueue.pop();
        return nextNode;
    }
    return -1;
}

TreeType Session::getTreeType() const
{
    return treeType;
}

void Session::writeJson(json &js)
{
}

void Session::readJson(const json &js)
{
    std::vector<std::vector<int>> matrix;
    js.at("graph").get_to(matrix);
    g = Graph(matrix);

    isCarrier = std::vector<bool>(matrix[0].size(), false);

    std::string treeTypeJs = js["tree"];
    if (treeTypeJs == "M")
    {
        treeType = MaxRank;
    }
    else
    {
        if (treeTypeJs == "C")
        {
            treeType = Cycle;
        }
        else
        {
            treeType = Root;
        }
    }

    for (auto &elem : js.at("agents"))
    {
        std::string agentType = elem[0];
        int nodeIndex = elem[1];
        if (agentType == "V")
        {
            addAgent(Virus(nodeIndex, *this));
        }
        else
        {
            addAgent(ContactTracer(*this));
        }
    }
}
void Session::infectNode(int nodeInd)
{
    g.infectNode(nodeInd);
}

bool Session::isInfected(int nodeInd)
{
    g.infectNode(nodeInd);
}

std::vector<int> Session::getNodeNeighbors(int nodeInd) const
{
    return g.getNodeNeighbors(nodeInd);
}
void Session::remove(int nodeInd)
{
    g.remove(nodeInd);
}

bool Session::isVirusCarrier(int nodeInd) const
{
    return isCarrier[nodeInd];
}

int Session::getCurrCycleInd() const
{
    return currCycleInd;
}

Tree *Session::BFS(int nodeInd) const
{
    std::vector<int> neighbors = getNodeNeighbors(nodeInd);
    std::vector<bool> setVisited(g.graphSize(), false);

    std::queue<Tree *> queueBFSTree;

    Tree *root = Tree::createTree(*this, nodeInd);
    setVisited[nodeInd] = true;
    queueBFSTree.push(root);

    while (!queueBFSTree.empty())
    {
        Tree *currTree = queueBFSTree.front();
        int currNode = currTree->getCurrNode();
        queueBFSTree.pop();

        neighbors = getNodeNeighbors(currNode);

        for (int i = 0; i < neighbors.size(); i++)
        {
            if (!setVisited[neighbors[i]])
            {
                Tree *child = Tree::createTree(*this, neighbors[i]);
                setVisited[neighbors[i]] = true;
                queueBFSTree.push(child);
                currTree->addChild(*child);
            }
        }
        if (currTree != root)
        {
            delete (currTree);
        }
    }

    return root;
}
