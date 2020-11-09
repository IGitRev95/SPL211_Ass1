#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"
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
    void disconnect(int node);//disconnecting node from the graph
    int getNumOfVertices() const;
    void clean();
    std::vector<int> getEdgesOf(int v) const;

    Tree* BFS_Scan(int rootNode, const Session& session);

    bool SessionDone(); // checking if the Session done
    bool Connected(int v1,int v2) const;
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> IsInfectedArray;

};

#endif
