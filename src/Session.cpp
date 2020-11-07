//
// Created by spl211 on 03/11/2020.
//

#include "include/Session.h"
#include <iostream>
#include <fstream>
#include "include/json.hpp"


using namespace std;
using json = nlohmann::json;
void Session::simulate() {
    bool HasChanged= true;
    int CycleNumber=0;
    while (HasChanged) {
        CycleNumber=+1;
        HasChanged= false;
        int i = agents.size();
        for (int j = 0; j <= i; j = +1) {
          agents.at(i)->act(*this);
          if(!HasChanged&&agents.at(i)->getMakeChanges())
            HasChanged=agents.at(i)->getMakeChanges();
        }
    }
    //make output json
}
Session::Session(const string &path): g(), treeType(),agents(),infecteds() {
    json input_data;
    ifstream jasonIn(path);
    jasonIn >> input_data;
  //  cout<<input_data["agents"]<<endl;
  vector<int> CarryNodes= {};
  int CarryNode;
    for (auto &elem: input_data["agents"]) {
        Agent* agent;
        if (elem.front() == "C") agent= new ContactTracer();
        else {
            CarryNode=elem.at(1);
            agent = new Virus(CarryNode);
            CarryNodes.push_back(CarryNode);
        }
        addAgent(*agent);
        delete agent;
    }
    g.updatematrix(input_data["graph"], CarryNodes);
    string tree= input_data["tree"].front();
    if (tree=="M") treeType=MaxRank;
    if (tree == "C") treeType=Cycle;
    if (tree == "R") treeType=Root;
    }
int Session::dequeueInfected() {
    int number= infecteds.front();
    infecteds.pop();
    return number;
}
void Session::enqueueInfected(int number) {
    infecteds.push(number);
}
TreeType Session::getTreeType() const {
    return treeType;
}
Graph* Session::getPointerGraph() {
    return (&this->g);
}
// Graph& Session::getGraph()  {
//    return g;
//}
        void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());}
//     //TODO:Need to make a copy constructor or assignment constructor
//    //TODO:set a tree type
//    //TODO: make a method that pulls the agents starting list from json and add to agents field using add_agent
//    Session::Session(const Session& other): g(),agents(),treeType(other.treeType),infecteds(other.infecteds) {
//        g=Graph(other.g);
//        for (Agent* agent: other.agents) agents.push_back(agent);
//
//        }
//


//    void Session:: copy(const Session& other) {
//        g = Graph(other.g);
//        treeType = other.treeType;
//    }



