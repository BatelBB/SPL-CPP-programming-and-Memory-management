#include <vector>
	#include <string>
	#include "Session.h"
	#include "Agent.h"
	#include "Graph.h"
	#include "json.hpp"
	#include <iostream>
	#include <fstream>
	

	using json = nlohmann::json;
	using namespace std;
	

	Session::Session(const std::string& path):currentCycle(0)
	{
	    // read a JSON file
	    ifstream i(path);
	    json j;
	    i >> j;
	

	    this->from_json(j);
	}
	

	json Session::to_json() 
	{
	    json j;
	    j["graph"] = g.getEdges();
	    j["infected"] = g.getInfected();
	    return j;
	    
	}
	

	void Session::from_json(const json& j) 
	{
	    // initialize g
	    vector<vector<int>> matrix;
	    j.at("graph").get_to(matrix);
	    g = Graph(matrix);
	

	    //initialize hasVirus
	    hasVirus = vector<bool>(matrix[0].size(),false);
	

	    //initialize treeType
	    string treeLetter = j["tree"];
	    if (treeLetter == "M")
	    {
	        treeType = MaxRank;
	    }
	    else
	    {
	        if (treeLetter == "C")
	        {
	            treeType = Cycle;
	        }
	        else
	        {
	            treeType = Root;
	        }  
	    }
	    
	

	    // initialize agents
	    for (auto& el : j.at("agents"))
	    {
	        std::string agentType = el[0];
	        int nodeInd = el[1];
	        if (agentType == "V")
	        {
	            addAgent(Virus(nodeInd , *this));
	        }
	        else
	        {
	            addAgent(ContactTracer(*this));
	        }
	    }
	}
	

	// might not be the best idea to just delegate to g
	void Session::infectNode(int nodeInd)
	{
	    g.infectNode(nodeInd);
	}
	bool Session::isInfected(int nodeInd)
	{
	    return g.isInfected(nodeInd);
	}
	std::vector<int> Session::getNeighbours(int nodeInd) const
	{
	    return g.getNeighbours(nodeInd);
	}
	void Session::isolate(int nodeInd)
	{
	    g.isolate(nodeInd);
	}
	

	

	// when a virus is added, hasVirus is updated
	void Session::addAgent(const Agent& agent)
	{
	    // need to clone agent to add to list, according to forum post
	    // https://www.cs.bgu.ac.il/~spl211/Assignments/Assignment_1Forum?action=show-thread&id=4292df802b6b39d3b33a6db7d72bec99
	    agents.push_back(agent.clone());
	

	    int nodeInd = agent.getNodeInd();
	    if (nodeInd!= -1)
	    {
	        hasVirus[nodeInd] = true;
	    }      
	}
	

	

	bool Session::hasVirusAt(int nodeInd) const
	{
	    return hasVirus[nodeInd];
	}
	

	

	void Session::enqueueInfected(int nodeInd)
	{
	    infectedQueue.push(nodeInd);
	}
	

	int Session::dequeueInfected()
	{
	    if(!infectedQueue.empty())
	    {
	        int nextInfected = infectedQueue.front();
	        infectedQueue.pop();
	        return nextInfected;
	    }
	    return -1;
	}
	

	int Session::getCurrentCycle() const
	{
	    return currentCycle;
	}
	

	

	Tree* Session::BFS(int nodeInd) const
	{
	    vector<int> neighbours = getNeighbours(nodeInd);
	

	    vector<bool> visited(g.size(), false);
	  
	    // Create a queue for BFS 
	    queue<Tree *> BFSqueue; 
	  
	    Tree* root = Tree::createTree(*this,nodeInd);
	    // Mark the current node as visited and enqueue it 
	    visited[nodeInd] = true; 
	    BFSqueue.push(root); 
	

	    
	  
	    //This is gonna be a bitch to debug lol
	    while(!BFSqueue.empty()) 
	    { 
	        // Dequeue a vertex from queue 
	        Tree* currentTree = BFSqueue.front(); 
	        int currentNode = currentTree->getNode();
	        BFSqueue.pop();
	

	        neighbours = getNeighbours(currentNode);
	

	        int childNum = 0;
	        for (int i=0; i<neighbours.size() ; i++)
	        {
	            
	            if (!visited[neighbours[i]])
	            {   // need to delete child?
	                Tree* child = Tree::createTree(*this,neighbours[i]);
	                visited[neighbours[i]] = true;
	                
	                currentTree->addChild(*child);
	                BFSqueue.push(currentTree->getChildren()[childNum]);
	                childNum++;
	            }
	        } 
	    }
	

	    return root;
	}
	

	

	TreeType Session::getTreeType() const
	{
	    return treeType;
	}
	

	void Session::simulate()
	{
	    bool finished = false;
	

	    while (!finished)
	    {
	        vector<Agent*> copyAgents;
	        for (int i=0; i<agents.size(); i++)
	        {
	            copyAgents.push_back(agents[i]->clone());
	        }
	        for (int i=0; i<copyAgents.size(); i++)
	        {
	            (*copyAgents[i]).act();
	        }
	

	        finished = true;
	        for (int i=0; i<hasVirus.size(); i++)
	        {
	            if (hasVirusAt(i) != isInfected(i))
	            {
	                finished = false;
	            }
	        }
	    }
	}

