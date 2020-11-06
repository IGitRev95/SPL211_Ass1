#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:

    void updatematrix (const std::vector<std::vector<int>>& matrix);

    Graph();

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;

private:
    std::vector<std::vector<int>> edges;
};

#endif
