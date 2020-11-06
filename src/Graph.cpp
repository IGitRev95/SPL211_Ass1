//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Graph.h"

using namespace std;

void Graph::updatematrix(const std::vector<std::vector<int>>& matrix) {
    for(vector<int> edge: matrix) edges.push_back(edge);
}
Graph::Graph(): edges(){};
// copy Constructor
Graph::Graph(const Graph& other):edges(other.edges) {};
