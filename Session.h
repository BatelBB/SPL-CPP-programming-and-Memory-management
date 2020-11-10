#ifndef SESSION_H_
	#define SESSION_H_
	

	#include <vector>
	#include <string>
	#include "Graph.h"
	#include "Tree.h"
	#include "json.hpp"
	#include <queue>
	

	class Agent;
	

	enum TreeType{
	  Cycle,
	  MaxRank,
	  Root
	};
	

	class Session{
	public:
	    Session(const std::string& path);
	    
	    void simulate();
	    void addAgent(const Agent& agent);
	    void setGraph(const Graph& graph);
	    
	    void enqueueInfected(int);
	    int dequeueInfected();
	    TreeType getTreeType() const;
	

	    // hasVirusAt should check if there's a virus agent at the given id
	    bool hasVirusAt(int nodeInd) const;
	

	    //should just invoke these functions on g
	    void infectNode(int nodeInd);
	    bool isInfected(int nodeInd);
	    std::vector<int> getNeighbours(int nodeInd) const;
	    void isolate(int nodeInd);
	

	    nlohmann::json to_json();
	    void from_json(const nlohmann::json& j);
	

	    int getCurrentCycle() const;
	

	    //BFS implementation
	    Tree* BFS(int nodeInd) const;
	

	    
	

	private:
	    Graph g;
	    TreeType treeType;
	    std::vector<Agent*> agents;
	

	    std::vector<bool> hasVirus;
	

	    std::queue<int> infectedQueue;
	

	    int currentCycle;
	};
	

	#endif

