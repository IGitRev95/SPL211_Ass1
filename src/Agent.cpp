//
// Created by spl211 on 03/11/2020.
//

#include "include/Agent.h"

using namespace std;
//Agent-
Agent::Agent(): MakeChanges(true) {}
bool Agent:: getMakeChanges() const{
    return MakeChanges;
}

//ContactTracer-
ContactTracer:: ContactTracer(): Agent(){}

void ContactTracer::act(Session &session) {
    if(!session.isInfectedQueueEmptey())
    {
        int root = session.dequeueInfected();
        Tree *curr_infected_tree = Tree::createTree(session,root);
        int node_to_disconnect = curr_infected_tree->traceTree();
        Graph phi(session.getGraphReference());//--!!on stack
        phi.disconnect(node_to_disconnect);
        //session.setGraph(phi); //!they said that not need to implement
        /*TODO: creat tree matching session treetype using BFS
          call traceTree method for picking node for disconnecting
          disconnect node and update relevant fields
         */
    }
}
Agent *ContactTracer:: clone() const {
    return new ContactTracer();
}
//Virus
Virus:: Virus(int nodeInd): Agent(), nodeInd(nodeInd) {}
void Virus::act(Session &session) {
    MakeChanges= false;
    int v= this->nodeInd;
    Graph& current= session.getGraphReference();
    if (!(current.isInfected(v))) {
        MakeChanges=true;
        current.infectNode(v);
        session.enqueueInfected(v);
    }
    vector<int> currentNodeEdges= current.getEdgesOf(v);
    int size= currentNodeEdges.size();
    for (int i=0;i<size;i=i+1){
        if(i!=v&& currentNodeEdges.at(i)==1&&current.NodeStatus(v)==0){
            MakeChanges=true;
          current.CarryNode(i);
            Virus *vi;
            vi = new Virus(i);
          session.addAgent(*vi);
            delete vi;
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




