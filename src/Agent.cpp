//
// Created by spl211 on 03/11/2020.
//

#include "include/Agent.h"
#include "include/Tree.h"
using namespace std;

Agent::Agent(): MakeChanges(true) {}

ContactTracer:: ContactTracer(): Agent(){}

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
