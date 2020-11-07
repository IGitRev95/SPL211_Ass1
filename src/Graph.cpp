//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Graph.h"

using namespace std;
//Graph::Graph(const std::vector<std::vector<int>>& matrix):edges(matrix) {};
void Graph::updatematrix(const std::vector<std::vector<int>>& matrix, const std::vector<int>& CarryNodes){
    for(vector<int> edge: matrix) {
        edges.push_back(edge);
        IsInfectedArray.push_back(0);
    }
    for (int i=0;i<=CarryNodes.size();i=i+1){
        IsInfectedArray.at(CarryNodes.at(i))=1;
    }
}
int Graph::NodeStatus(int nodeInd) {
    return IsInfectedArray.at((nodeInd));
}
bool Graph::isInfected(int nodeInd) {
    return NodeStatus(nodeInd)==2;
}
void Graph::infectNode(int nodeInd) {
    if (!isInfected(nodeInd)) IsInfectedArray.at(nodeInd)=2;
}
void Graph::CarryNode(int nodeInd) {
    if (!isInfected(nodeInd)) IsInfectedArray.at(nodeInd)=1;
}
vector<int> Graph::getEdgesOf(int v) const {
    return edges.at(v);
}
Graph::Graph(): edges(), IsInfectedArray(){}
// copy Constructor
Graph::Graph(const Graph& other):edges(other.edges) {}
