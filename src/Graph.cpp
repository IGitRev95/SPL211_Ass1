//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Session.h"
#include "include/Graph.h"


using namespace std;
//Graph::Graph(const std::vector<std::vector<int>>& matrix):edges(matrix) {};
void Graph::updateMatrix(const std::vector<std::vector<int>>& matrix, const std::vector<int>& CarryNodes){
    for(vector<int> edge: matrix) {
        edges.push_back(edge);
        IsInfectedArray.push_back(0);
    }
    for (int i=0;i<CarryNodes.size();i=i+1){
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

int Graph::getNumOfVertices() const {
    return edges.size();
}

Graph& Graph::operator=(const Graph& other)
{
    int verticesNum = other.edges.size();
    for(int row=0; row < verticesNum; row= row + 1)// maybe can use assignment operator of vector class?
    {
        for(int column = 0; column < verticesNum; column= column + 1)
        {
            edges.at(row).at(column)=other.edges.at(row).at(column);
        }
    }
    IsInfectedArray=other.IsInfectedArray;
    return *this;
}

bool Graph:: Connected(int v1, int v2) const{
    if (v1!=v2) return (edges.at(v1).at(v2)==1);
    return false;
}

bool Graph::SessionDone() {
    int size= edges.size();
    bool  terminate=true;
    int StatusCurrent;
    for (int i=0;terminate&& i < size; i= i + 1) {
        StatusCurrent = NodeStatus(i);
        if (StatusCurrent == 1) terminate = false;
        else {
            for (int j = i + 1; terminate && j < size; j = j + 1) {
                if (Connected(i, j) && StatusCurrent != NodeStatus(j))
                    terminate = false;
            }
        }
    }}

Tree* Graph::BFSScan(int rootNode) {

    int numOfvert = getNumOfVertices();
    vector<vector<int>> bfsData(numOfvert);
    /*
     * table of [0]color,[1]distance,[2]parent
     */
    for(auto &vec: bfsData)
    {
        vec.push_back(0);
        vec.push_back(0);
        vec.push_back(-1);
    }
    bfsData.at(rootNode).at(0)=1;
    queue<int> bfsQ;
    bfsQ.push(rootNode);
    while (!bfsQ.empty())
    {
        int u = bfsQ.front();
        bfsQ.pop();
        for(int v : getEdgesOf(u))
        {
            if (bfsData.at(v).at(0)==0)
            {
                bfsData.at(v).at(0)=1;
                bfsData.at(v).at(1)=bfsData.at(u).at(1)+1;
                bfsData.at(v).at(2)=u;
                bfsQ.push(v);
            }
        }
        bfsData.at(u).at(0)=3;
    }
//------------------------------------------------
    //MEMORY LEAK OPTION
    vector<Tree*> nodes_control(numOfvert);
    for(int i=0;i<nodes_control.size();i=i+1)//nodes initiation
    {
//        nodes_control.at(i) = Tree::createTree(session, i);
    }

    for (int i = 0; i < nodes_control.size(); i=i+1)
    {
        nodes_control.at(bfsData.at(i).at(2))->addChild(*nodes_control.at(i));
    }

    Tree* ans(nodes_control.at(rootNode)->clone());
    for(int i=0;i<nodes_control.size();i=i+1)//nodes initiation
    {
        delete nodes_control.at(i);
    }
    return ans;
}

void Graph:: clean(){
    edges.clear();
    IsInfectedArray.clear();
}