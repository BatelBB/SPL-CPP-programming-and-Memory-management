#include <iostream>
#include "json.hpp"
#include <fstream>
#include "Graph.h"

using json = nlohmann::json;

Graph::Graph()
{
}
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), isInfectedVec(std::vector<bool>(matrix[0].size(), false))
{
}
/**{

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

//}

// CPP program to convert Adjacency matrix
// representation to Adjacency List

// converts from adjacency matrix to adjacency list
/**std::vector<std::vector<int>> convert( std::vector<std::vector<int>> a) 
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
    isInfectedVec[nodeInd] = true;
}
bool Graph::isInfected(int nodeInd)
{
    return isInfectedVec[nodeInd];
}

std::vector<int> Graph::getNodeNeighbors(int nodeInd) const
{
    std::vector<int> nodeNeighbors;
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[nodeInd][i] == 1)
        {
            nodeNeighbors.push_back(i);
        }
    }
    return nodeNeighbors;
}

void Graph::remove(int nodeInd)
{
    for (int i = 0; i < edges.size(); i++)
    {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;

    }
}

int Graph::graphSize() const
{
    return edges[0].size();
}

std::vector<std::vector<int>> Graph::getGraph() const {
    return edges;
}

std::vector<int> Graph::getInfectedNodes() const{
    std::vector<int> currNodeInfected;
    for(int i=0; i<isInfectedVec.size(); i++){
        if (isInfectedVec[i]){
            currNodeInfected.push_back(i);
        }
    }
    return currNodeInfected;
}
