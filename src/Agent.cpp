#include <vector>
#include "Agent.h"
#include "Tree.h"

//default constructor
Agent::Agent() {}

//destructor
Agent::~Agent() {}

//constructor
ContactTracer::ContactTracer() {}

//checks the top node of the infected queue, if there is an infected node it starts to act and separates the node
void ContactTracer::act(Session &session) {
    if (session.getQSize() != 0) {
        int topNode = session.dequeueInfected();

        //checks if the top node in the queue is infected, if not it will return -1.
        if (topNode != -1) {
            Tree *currNode = session.BFS(topNode);
            int nodeToSeparate;
            nodeToSeparate = currNode->traceTree();
            session.separateNode(nodeToSeparate);
            delete currNode;
        }
    }
}

//creates a new contact tracer
Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

//getter - returns the index number that the contact tracer is on
int ContactTracer::getNodeInd() const {
    return -1;
}

//constructor
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

//checks if the node is infected, if it's not then it infects it and puts it inside the infected queue
//creates a vector of the neighbors of the node, and runs on it to spread the virus
void Virus::act(Session &session) {

    if (!session.isInfected(nodeInd)) {
        session.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }

    std::vector<int> nodeNeighbors = session.getNodeNeighbors(nodeInd);

    int nodeNeighborsSize = nodeNeighbors.size(); //to deal with the unsigned integer
    for (int i = 0; i < nodeNeighborsSize; i++) {
        if (!session.isCarrierAt(nodeNeighbors[i])) {
            Virus spreadVirus(nodeNeighbors[i]);
            session.addAgent(spreadVirus);
            break;
        }
    }
}

//creates a new virus
Agent *Virus::clone() const {
    return new Virus(*this);
}

// getter - returns the node index that the virus is currently on
int Virus::getNodeInd() const {
    return nodeInd;
}

