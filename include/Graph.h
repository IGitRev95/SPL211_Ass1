#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:

    void updatematrix (const std::vector<std::vector<int>>& matrix);

    Graph();
  //  Graph(const std::vector<std::vector<int>>& matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Graph(const Graph& other); // copy constructor
    Graph& operator=(const Graph& other); // copy assignment operator
    Graph(Graph&& other) noexcept; // move constructor
    Graph& operator=(Graph&& other) noexcept; // move assigment operator

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> IsInfectedArray;
};

#endif
