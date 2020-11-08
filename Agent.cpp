#include <iostream>
#include "Agent.h"
#include "Tree.h"
#include "Session.h"

Agent::Agent(Session &session) : session(session)
{
}
Agent::Agent *clone()
{
    return new Agent(*this);
}
void Agent::act()
{
}

ContactTracer::ContactTracer(Session &session) : Agent(session)
{
}
Agent *ContactTracer::clone()
{
    return new ContactTracer(*this);
}

void ContactTracer::act()
{
    int currentNode = session.dequeueInfected();

    if (currentNode != -1)
    {
        Tree *currTree = session.BFS(currentNode);
        int nodeToRemove = currTree->traceTree();
        session.remove(nodeToRemove);
        delete currTree;
    }
}
int ContactTracer::getNodeIndex() const
{
    return -1;
}

Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd)
{
}

Agent *Virus::clone()
{
    return new Virus(*this);
}

int Virus::getNodeIndex() const
{
    return nodeInd;
}

//This method does 2 things:
//first it checks if the node that it's currently in is infected - if not then it makes it infected - it takes from Session.h the "void enqueueInfected(int)"
//the second thing is that it goes through the node's neighbor, goes in ascending order and choose the smaller one to settle - just put the virus in it.
void Virus::act()
{
    if (!session.isInfected(nodeInd))
    {
        session.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }

    std::vector<int> neighbors = session.getNodeNeighbors(nodeInd);

    for (int i = 0; i < neighbors.size(); i++)
    {
        if (!session.isVirusCarrier(neighbors[i]))
        {
            Virus spreadVirus(neighbors[i], session);
            session.addAgent(spreadVirus);
            break;
        }
    }
}
