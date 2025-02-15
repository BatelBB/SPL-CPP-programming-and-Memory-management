#ifndef AGENT_H_
#define AGENT_H_


#include <vector>
#include "Session.h"


class Agent {
public:
    Agent();

    virtual void act(Session &session) = 0;


    virtual Agent *clone() const = 0;


    virtual int getNodeInd() const = 0;


    virtual ~Agent();
};


class ContactTracer : public Agent {
public:
    ContactTracer();

    virtual void act(Session &session);


    virtual Agent *clone() const;


    virtual int getNodeInd() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    virtual void act(Session &session);


    virtual Agent *clone() const;


    virtual int getNodeInd() const;


private:
    const int nodeInd;
};


#endif

