#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Agent
{

public:
    Agent(Session &session);
    virtual Agent *clone() const = 0;
    virtual void act() = 0;
    virtual int getNodeIndex() const;

protected:
    Session &session;
};

class ContactTracer : public Agent
{

public:
    ContactTracer(Session &session);
    virtual Agent *clone() = 0;
    virtual void act();

    virtual int getNodeIndex() const;
};

class Virus : public Agent
{

public:
    Virus(int nodeInd, Session &session);
    virtual Agent *clone() const;
    virtual void act();
    virtual int getNodeIndex() const;

protected:
    const int nodeInd;
};

#endif
