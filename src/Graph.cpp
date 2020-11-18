//
// Created by spl211 on 03/11/2020.
//
#include <string>
#include "include/Session.h"
#include "include/Graph.h"

/**
 * at edges 1 between v1,v2 means they are connected
 * at IsinfectedArray 0- means not infected, 1- means Carry 2- means infected
 */
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),IsInfectedArray() {};

const vector<vector<int>>& Graph::GetEdges() const {
return edges;
}
void Graph::updateMatrix(const std::vector<std::vector<int>>& matrix, const std::vector<int>& CarryNodes){
    edges.clear();
    IsInfectedArray.clear();
    for(vector<int> edge: matrix) {
        edges.push_back(edge);
        IsInfectedArray.push_back(0);
    }
    for (unsigned int i=0;i<CarryNodes.size();i=i+1){
        IsInfectedArray.at(CarryNodes.at(i))=1;
    }
}

int Graph::NodeStatus(int nodeInd) {
    //0- nof infected, 1- carry, 2- infected
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

const vector<int>& Graph::getEdgesOf(int v) const {
    return edges.at(v);
}

Graph::Graph(): edges(), IsInfectedArray(){}

// copy Constructor
Graph::Graph(const Graph& other):edges(other.edges),IsInfectedArray(other.IsInfectedArray) {}

//Disconnect
void Graph::disconnect(int node) {
    const int numOfVertices=edges.size();
    for(int i=0;i<numOfVertices;i=i+1)
    {
        edges.at(node).at(i)=0;
    }

    for(int i=0;i<numOfVertices;i=i+1)
    {
        edges.at(i).at(node)=0;
    }
}

int Graph::getNumOfVertices() const {
    return edges.size();
}

Graph& Graph::operator=(const Graph& other)
{
   edges=other.edges;
    IsInfectedArray=other.IsInfectedArray;
//    int verticesNum = other.edges.size();
//    for(int row=0; row < verticesNum; row= row + 1)// maybe can use assignment operator of vector class?
//    {
//        for(int column = 0; column < verticesNum; column= column + 1)
//        {
//            edges.at(row).at(column)=other.edges.at(row).at(column);
//        }
//    }
//    IsInfectedArray=other.IsInfectedArray;
    return *this;
}

bool Graph:: Connected(int v1, int v2) const{
    if (v1!=v2) return (edges.at(v1).at(v2)==1);
    return false;
}
// checking if the session is done
bool Graph::SessionDone() {
    int size= edges.size();
    bool  terminate=true;
    int StatusCurrent;
    for (int i=0;terminate&& i < size; i= i + 1) {
        StatusCurrent = NodeStatus(i);
        if (StatusCurrent == 1) terminate=false;
        else{
            for (int j=i+1;terminate&&j<size;j=j+1){
                if (Connected(i,j)&&StatusCurrent!=NodeStatus(j))
                    terminate=false;
            }
        }
    }
    return terminate;
}

Graph* Graph::BFSScan(int rootNode) const {//BFS version returns bfs tree as graph, each node[i] know its children
    int numOfVert = getNumOfVertices();
    std::vector<std::vector<int>> bfsData(numOfVert);
    /*
     * table of [0]color,[1]distance,[2]parent
     */
    //simple definitions
    const int color(0);
    const int distance(1);
    const int parent(2);
    const int colorWhite(0);
    const int colorGray(1);
    const int colorBlack(2);
    const int noParent(-1);
    for(vector<int> &vec: bfsData)//init of verticed data
    {
        vec.push_back(colorWhite);
        vec.push_back(0);
        vec.push_back(noParent);
    }

    bfsData.at(rootNode).at(color)=colorGray;
    queue<int> bfsQ;
    bfsQ.push(rootNode);
    while (!bfsQ.empty()) //BFS run - implemented as an interpretation to algorithm from DS course
    {
        int currVerix = bfsQ.front();
        bfsQ.pop();
        int vertixCandidateNeghiber=0;
        for(int edgeIndicator : getEdgesOf(currVerix))
        {
            if(edgeIndicator == 1) {
                if (bfsData.at(vertixCandidateNeghiber).at(color) == colorWhite) {
                    bfsData.at(vertixCandidateNeghiber).at(color) = colorGray;
                    bfsData.at(vertixCandidateNeghiber).at(distance) = bfsData.at(currVerix).at(distance) + 1;
                    bfsData.at(vertixCandidateNeghiber).at(parent) = currVerix;
                    bfsQ.push(vertixCandidateNeghiber);
                }
            }
            vertixCandidateNeghiber= vertixCandidateNeghiber + 1;
        }
        bfsData.at(currVerix).at(color)=colorBlack;
    }
    return BFSDataToGraph(bfsData);
}

Graph* Graph::BFSDataToGraph(std::vector<std::vector<int>> BFSdata) const {
    int numofVertix(BFSdata.size());
    std::vector<std::vector<int>> bfsMatrix(numofVertix,vector<int>(numofVertix,0) );

    for (int i = 0; i < numofVertix; i=i+1)
    {
        int parent(BFSdata.at(i).at(2));
        bool haveParent(-1!=parent);
        if(haveParent) {
            bfsMatrix.at(parent).at(i)=1;//each node pulls an edge from its' parent to itself
        }
    }
    return new Graph(bfsMatrix);//directed graph edge from row to col
}

void Graph:: clean(){
    edges.clear();
    IsInfectedArray.clear();
}