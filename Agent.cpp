#include <vector>
#include "Agent.h"
#include "Tree.h"


Agent::Agent() {}


Agent::~Agent() {}

ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {
    int topNode = session.dequeueInfected();

    if (topNode != -1) {
        Tree *currNode = session.BFS(topNode);
        int nodeToSeparate = currNode->traceTree();
        session.separateNode(nodeToSeparate);
        delete currNode;
    }
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


int ContactTracer::getNodeInd() const {
    return -1;
}


Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

void Virus::act(Session &session) {

    if (!session.isInfected(nodeInd)) {
        session.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }

    std::vector<int> nodeNeighbors = session.getNodeNeighbors(nodeInd);


    int neighboursSize = nodeNeighbors.size(); //Batel - to deal with the unsigned integer
    for (int i = 0; i < neighboursSize; i++) {
        if (!session.isCarrierAt(nodeNeighbors[i])) {
            Virus spreadVirus(nodeNeighbors[i]);
            session.addAgent(spreadVirus);
            break;
        }
    }
}

Agent *Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNodeInd() const {
    return nodeInd;
}

