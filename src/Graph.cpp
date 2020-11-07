//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Graph.h"

using namespace std;
//Graph::Graph(const std::vector<std::vector<int>>& matrix):edges(matrix) {};
void Graph::updatematrix(const std::vector<std::vector<int>>& matrix) {
    for(vector<int> edge: matrix) edges.push_back(edge);
}
Graph::Graph(): edges(){};
// copy Constructor
Graph::Graph(const Graph& other):edges(other.edges) {};

//Disconnect
void Graph::disconnect(int node) {

    for(int i=0;i<edges.size();i=i+1)
    {
        edges.at(node).at(i)=0;
    }

    for(int i=0;i<edges.size();i=i+1)
    {
        edges.at(i).at(node)=0;
    }
}

