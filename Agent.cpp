#include <iostream>
#include "Agent.h"


    Agent(Session& session);
     virtual Agent* clone(){
        return new Agent(*this);
    };
    virtual void act()=0;



    ContactTracer(Session& session);
    virtual Agent* clone(){
        return new ContactTracer(*this);
    };
    virtual void act();




    Virus(int nodeInd, Session& session);
    virtual Agent* clone(){
        return new Virus(*this);
    };
    virtual void act();


