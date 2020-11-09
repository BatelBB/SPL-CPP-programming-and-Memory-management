#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "Tree.h"
#include "json.hpp"

class Agent;

enum TreeType
{
  Cycle,
  MaxRank,
  Root
};

class Session
{
public:
  //write Json file
  json writeJson();

  //read from the Json file
  void readJson(const nlohmann::json &js);

  //Our Method - from screenshot
  //default constructor(?)
  Session(const Session &other);

  //demonstrates the path that the agents (virus/contact tracer) are doing
  Session(const std::string &path);

  //creates the json file that suppose to show stuff
  void simulate();

  //taking the agent from the json file and adding it to the cycle - NOT SURE ABOUT THIS ONE
  //maybe uses the "std::vector<Agent*> agents;" that's down here?
  void addAgent(const Agent &agent);

  //taking the graph from the contact tracer and setting it to be the current one - NOT SURE ABOUT THIS ONE
  //I think it supposed to set the "Graph g;" that's in the private down here
  void setGraph(const Graph &graph);

  //takes the infected nodes and sends them to the queue
  void enqueueInfected(int);

  //the contact tracer uses this method to take out the infected nodes that it already used
  int dequeueInfected();

  //returns the tree type - MaxRankTree/RootTree/CycleTree
  //maybe returns the "TreeType treeType;" that's down here?
  TreeType getTreeType() const;

  //returns true/false according to the virus situation in the current node
  bool isVirusCarrier(int nodeInd) const;

  //from "Graph.h"
  void infectNode(int nodeInd);

  //from "Graph.h"
  bool isInfected(int nodeInd);

  //from "Graph.h"
  std::vector<int> getNodeNeighbors(int nodeInd) const;

  //from "Graph.h"
  void remove(int nodeInd);

  //returns the integer of the current cycle in the current flow
  int getCurrCycleInd() const;

  //BFS implementation
  Tree *BFS(int nodeInd) const;

private:
  Graph g;
  TreeType treeType;
  std::vector<Agent *> agents;
  std::queue<int> infectedQueue;
  std::vector<bool> isCarrier;
  int currCycleInd;
};

#endif
