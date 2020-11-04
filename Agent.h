#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
//I'm not sure about this class at all, it represents the different agents, not sure what it does.
class Agent{
public:
    Agent(Session& session);
    virtual Agent* clone()=0;
    virtual void act()=0;
protected:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual Agent* clone();
    virtual void act();
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual Agent* clone();
    virtual void act();
protected:
    const int nodeInd;
};

#endif
