#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Session.h"

using json = nlohmann::json;

    std::ifstream ifs("/home/spl211/Assignment1/Test/config1.json");
    json js = json::parse(ifs);
    
    //Our Method - Dolav Screenshot
    Session::Session(const Session& other):g(), treeType(other.treeType), agents(){
        for(int i=0; i<other.agents.size(); ++i){
            Agent* newAgent = other.agents[i].clone();
            agents.push_back(newAgent);
        }
    }

    //the initilization and the mimush is from Dolav video
    Session::Session(const std::string& path):g(std::vector<std::vector<int>>()){
        g = Graph(js["graph"]);

        //screenshot from students
        std::vector<std::vector<int>> matrix = js["graph"];
    };
    
    Session.addAgent(Virus(2));            //We add from the screenshote
    
    addAgent(const Agent& agent){          
        Agent* clone = agent.clone();      //We add from the screenshote
    }
    
    
    void simulate();{
        
    }


    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph){
       something = graph;
    }
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const{
        return ;
    }
    

 
