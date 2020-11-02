#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream> 
#include "Graph.h"


using json = nlohmann::json;

       

    Graph::Graph(std::vector<std::vector<int>> matrix){
        
        std::ifstream ifs("/home/spl211/Assignment1/config1.json");
        json jf = json::parse(ifs);
        size_t mSize = matrix.size();
        matrix = jf["graph"];
        for(int i=0; i<mSize; i++){
            
        }

  // Initialize the matrix to zero
  Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) {
      adjMatrix[i] = new bool[numVertices];
      for (int j = 0; j < numVertices; j++)
        adjMatrix[i][j] = false;
    }
      // Print the martix
     void toString() {
     for (int i = 0; i < numVertices; i++) {
       cout << i << " : ";
       for (int j = 0; j < numVertices; j++)
        cout << adjMatrix[i][j] << " ";
          cout << "\n";
    }
    }

   
    
    void Graph::infectNode(int nodeInd){

    }
    bool Graph::isInfected(int nodeInd){

    }

   
