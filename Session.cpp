#include <iostream>
#include "Session.h"



    //TODO
    Session::Session(const std::string& path){
        
    }

    
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    Session::TreeType getTreeType() const;
    

 