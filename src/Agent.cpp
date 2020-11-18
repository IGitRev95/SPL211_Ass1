//
// Created by spl211 on 03/11/2020.
//
#include<iostream>
#include "include/Agent.h"

using namespace std;
//Agent-
Agent::Agent()= default;
Agent::~Agent()=default;


//ContactTracer-
ContactTracer:: ContactTracer(): Agent(){}

void ContactTracer::act(Session &session) {
    int root = session.dequeueInfected();
    if(root!=-1)
    {
        Tree *curr_infected_tree = Tree::createTree(session,root);
        int node_to_disconnect = curr_infected_tree->traceTree();
        session.getGraphReference().disconnectNode(node_to_disconnect);
        delete curr_infected_tree;
    }
}

Agent *ContactTracer:: clone() const {
    return new ContactTracer();
}

//Virus
Virus:: Virus(int nodeInd):nodeInd(nodeInd) {}

void Virus::act(Session &session) {
    int v= this->nodeInd;
    Graph& current= session.getGraphReference();
    if (!(current.isInfected(v))) {
        current.infectNode(v);
        session.enqueueInfected(v);
    }
    vector<int> currentNodeEdges= current.getEdgesOf(v);
    int size= currentNodeEdges.size();
    for (int i=0;i<size;i=i+1){
        if(i!=v&& currentNodeEdges.at(i)==1&& current.getNodeStatus(i) == 0){
            current.MakeNodeCarry(i);
            Virus vi=Virus(i);
          session.addAgent(vi);
            break;
        }
    }
}

Agent* Virus::clone() const {
    return new Virus(this->getNumber());
}

int Virus::getNumber()  const {
    return nodeInd;
}




