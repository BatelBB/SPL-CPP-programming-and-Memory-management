#include <iostream>
#include "json.hpp"
#include <fstream>
#include "Graph.h"

using json = nlohmann::json;



Graph::Graph(std::vector<std::vector<int>> matrix)
{

    std::ifstream ifs("/home/spl211/Assignment1/Test/config1.json");
    json jf = json::parse(ifs);
    std::vector<std::vector<int>> matrix = jf["graph"];


   /*
    //Initialize the matrix to be the same as the one in the json file
    size_t mSize = jf["graph"].size();
    
    for (int i = 0; i < mSize; i++)
    {
        
        for (int j = 0; mSize; j++)
        {
            edges.push_back(jf["graph"][i][j]);
        }
        matrix.push_back(edges);
    }
*/
    
}

// CPP program to convert Adjacency matrix 
// representation to Adjacency List 
  
// converts from adjacency matrix to adjacency list 
std::vector<std::vector<int>> convert( std::vector<std::vector<int>> a) 
{ 
    std::vector<std::vector<int>> adjList(a.size()); 
    for (int i = 0; i < a.size(); i++) 
    { 
          
        for (int j = 0; j < a[i].size(); j++) 
        { 
            if (a[i][j] == 1) 
            { 
                adjList[i].push_back(j); 
            } 
        } 
    } 
    return adjList; 
} 
// Print the martix
/**
void toString()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << i << " : ";
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}
**/

void Graph::infectNode(int nodeInd)
{
}
bool Graph::isInfected(int nodeInd)
{
}

std::vector<std::vector<int>> edges() const{
    return edges;
}

