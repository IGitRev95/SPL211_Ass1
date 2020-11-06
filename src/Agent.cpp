//
// Created by spl211 on 03/11/2020.
//

#include "include/Agent.h"

using namespace std;
Agent::Agent(){}
ContactTracer:: ContactTracer(){}
Virus:: Virus(int nodeInd):nodeInd(nodeInd) {}

Agent *ContactTracer:: clone() const {
    return new ContactTracer();
}
Agent* Virus::clone() const {
    return new Virus(this->getNumber());
}
int Virus::getNumber()  const {
    return nodeInd;
}



// constructor for ContactTracer
