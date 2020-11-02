#include <iostream>
#include "Agent.h"


    Agent(Session& session);
    
    virtual void act()=0;



    ContactTracer(Session& session);
    
    virtual void act();




    Virus(int nodeInd, Session& session);
    
    virtual void act();


