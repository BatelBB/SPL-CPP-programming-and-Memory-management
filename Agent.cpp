#include "Agent.h"
	#include "Tree.h"
	#include <vector>
	

	

	Agent::Agent(Session& session): session(session){}
	

	ContactTracer::ContactTracer(Session& session):Agent(session){}
	

	void ContactTracer::act()
	{
	    int currentNode = session.dequeueInfected();
	    // assuming dequeueInfected returns -1 when no infected left
	    if (currentNode!= -1)
	    {
	        Tree* currentTree = session.BFS(currentNode);
	        int nodeToIsolate = currentTree->traceTree();
	        // isolate should remove all links to adjacent nodes to the given node
	        session.isolate(nodeToIsolate);
	        delete currentTree;
	    }
	}
	

	Agent* ContactTracer::clone() const
	{
	    return new ContactTracer(*this);
	}
	

	int ContactTracer::getNodeInd() const
	{
	    return -1;
	}
	

	

	

	Virus::Virus(int nodeInd, Session& session):Agent(session), nodeInd(nodeInd){}
	

	// act() makes the virus infect the node it occupies if it hadn't already, and spread to one virus-free neighbour if it can.
	void Virus::act()
	{
	    // The virus infects the current node as it's first action
	    if (!session.isInfected(nodeInd))
	    {
	        session.infectNode(nodeInd);
	        session.enqueueInfected(nodeInd);
	    }
	

	    //getNeighbors should return a sorted list of node ids that are adjacent to nodeInd
	    std::vector<int> neighbours = session.getNeighbours(nodeInd);
	

	    for (int i=0; i<neighbours.size() ; i++)
	    {
	        // hasVirusAt should check if there's a virus agent at the given id
	        if (!session.hasVirusAt(neighbours[i]))
	        {
	            // Check if it needs to be agent instead of virus, and how to pass to add agent properly
	            Virus cloneVirus(neighbours[i], session);
	            session.addAgent(cloneVirus);
	            break; // clones to one at a time.
	        }
	    }
	}
	

	Agent* Virus::clone() const
	{
	    return new Virus(*this);
	}
	

	int Virus::getNodeInd() const
	{
	    return nodeInd;
	}

