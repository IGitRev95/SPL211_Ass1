//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Graph.h"

using namespace std;
//Graph::Graph(const std::vector<std::vector<int>>& matrix):edges(matrix) {};
void Graph::updatematrix(const std::vector<std::vector<int>>& matrix){
    for(vector<int> edge: matrix) {
        edges.push_back(edge);
        IsInfectedArray.push_back(0);
    }
}
bool Graph::isInfected(int nodeInd) {
    return (IsInfectedArray.at(nodeInd)==1);
}
void Graph::infectNode(int nodeInd) {
    if (!isInfected(nodeInd)) IsInfectedArray.at(nodeInd)=1;
}
Graph::Graph(): edges(), IsInfectedArray(){}
// copy Constructor
Graph::Graph(const Graph& other):edges(other.edges) {}
