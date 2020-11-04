#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent{};

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //Our Method - from screenshot
    //default constructor(?)
    Session::Session(const Session& other);

    //demonstrates the path that the agents (virus/contact tracer) are doing
    Session(const std::string& path);
    
    //creates the json file that suppose to show stuff
    void simulate();

    //taking the agent from the json file and adding it to the cycle - NOT SURE ABOUT THIS ONE
    //maybe uses the "std::vector<Agent*> agents;" that's down here?
    void addAgent(const Agent& agent);

    //taking the graph from the contact tracer and setting it to be the current one - NOT SURE ABOUT THIS ONE
    //I think it supposed to set the "Graph g;" that's in the private down here
    void setGraph(const Graph& graph);
    
    //takes the infected nodes and sends them to the queue
    void enqueueInfected(int);

    //the contact tracer uses this method to take out the infected nodes that it already used
    int dequeueInfected();

    //returns the tree type - MaxRankTree/RootTree/CycleTree
    //maybe returns the "TreeType treeType;" that's down here?
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
