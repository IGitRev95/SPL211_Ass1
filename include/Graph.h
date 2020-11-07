#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:

    void updatematrix (const std::vector<std::vector<int>>& matrix, const std::vector<int>& CarryNodes);

    Graph();
  //  Graph(const std::vector<std::vector<int>>& matrix);
    void infectNode(int nodeInd);
    void CarryNode(int nodeInd);
    int NodeStatus(int nodeInd);
    bool isInfected(int nodeInd);
    Graph(const Graph& other); // copy constructor
    Graph& operator=(const Graph& other); // copy assignment operator
    Graph(Graph&& other) noexcept; // move constructor
    Graph& operator=(Graph&& other) noexcept; // move assigment operator

    void disconnect(int node);//disconnecting node from the graph

    std::vector<int> getEdgesOf(int v) const;
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> IsInfectedArray;
};

#endif
