//
// Created by spl211 on 03/11/2020.
//

#include "include/Agent.h"

using namespace std;
//Agent-
Agent::Agent()= default;
Agent::~Agent()=default;


//ContactTracer-
ContactTracer:: ContactTracer(): Agent(){}

void ContactTracer::act(Session &session) {
    int root = session.dequeueInfected();
    if(root!=-1) // -1:= queue is empty
    {
        Tree *curr_infected_tree = Tree::createTree(session,root); // create Bfs tree
        int node_to_disconnect = curr_infected_tree->traceTree(); // choosing node to disconnect
        session.getGraphReference().disconnectNode(node_to_disconnect);// disconnect chosen node
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
    if (!(current.isInfected(v))) { // if the node isnt infected
        current.infectNode(v); // let the node infected
        session.enqueueInfected(v); // push to the queue of infecteds
    }

    int size= current.getNumOfVertices();
    for (int i=0;i<size;i=i+1){
        // for other virus , if connected and the other not infected
        if(i!=v&& current.NodesAreConnected(v,i)&& current.getNodeStatus(i) == 0){
            current.MakeNodeCarry(i);
          session.addAgent(Virus(i));
            break;
        }
    }
}

Agent* Virus::clone() const {
    return new Virus(this->getNodeIndex());
}

const int Virus::getNodeIndex()  const {
    return nodeInd;
}




