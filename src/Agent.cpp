//
// Created by spl211 on 03/11/2020.
//

#include "include/Agent.h"
#include "include/Tree.h"
using namespace std;

Agent::Agent(): MakeChanges(true) {}
bool Agent:: getMakeChanges() const{
    return MakeChanges;
}

ContactTracer:: ContactTracer(): Agent(){}

Virus:: Virus(int nodeInd): Agent(), nodeInd(nodeInd) {}
void Virus::act(Session &session) {
    MakeChanges= false;
    int v= this->nodeInd;
    Graph* current= session.getPointerGraph();
    if (!(current->isInfected(v))) {
        MakeChanges=true;
        current->infectNode(v);
        session.enqueueInfected(v);
    }
    vector<int> currentNodeEdges= current->getEdgesOf(v);
    int size= currentNodeEdges.size();
    for (int i=0;i<=size;i=+1){
        if(i!=v&& currentNodeEdges.at(i)==1&&current->NodeStatus(v)==0){
            MakeChanges=true;
          current->CarryNode(i);
          Virus* virus= new Virus(i);
          session.addAgent(*virus);
            delete virus;
            break;
        }
    }
}
void ContactTracer::act(Session &session) {}
Agent *ContactTracer:: clone() const {
    return new ContactTracer();
}

void ContactTracer::act(Session &session) {
    if(!session.isInfectedQueueEmptey())
    {
        int root = session.dequeueInfected();
        Tree *curr_infected_tree = Tree::createTree(session,root);
        int node_to_disconnect = curr_infected_tree->traceTree();
        Graph phi(session.getG());//--!!on stack
        phi.disconnect(node_to_disconnect);
        session.setGraph(phi);
        /*TODO: creat tree matching session treetype using BFS
          call traceTree method for picking node for disconnecting
          disconnect node and update relevant fields
         */
    }
}

Virus:: Virus(int nodeInd): Agent(), nodeInd(nodeInd) {}

Agent* Virus::clone() const {
    return new Virus(this->getNumber());
}
int Virus::getNumber()  const {
    return nodeInd;
}



// constructor for ContactTracer
