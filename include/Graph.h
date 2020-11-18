#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include "Session.h"
#include "Tree.h"

class Session;
class Tree;

class Graph {
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);
    const std::vector<std::vector<int>>& GetEdges() const;
    void infectNode(int nodeInd);
    void MakeNodeCarry(int nodeInd); // make node carry
    int getNodeStatus(int nodeInd); // status of virus 0:= not infected 1:= carry 2:= infected
    bool isInfected(int nodeInd);
    const std::vector<int>& getEdgesOf(int v) const;
    void updateGraph (const std::vector<std::vector<int>>& matrix, const std::vector<int>& CarryNodes);
    Graph(const Graph& other); // copy constructor
    Graph& operator=(const Graph& other); // copy assignment operator
    void disconnectNode(int node);//disconnecting node from the graph
    int getNumOfVertices() const;
    bool NodesAreConnected(int v1, int v2) const;
    bool isSessionDone(); // checking if the session meeting termination conditions
    Graph* BFSScan(int rootNode) const;
    void clean();

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> IsInfectedArray;
    Graph* BFSDataToGraph(std::vector<std::vector<int>> BFSdata) const;
};

#endif
