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
    bool termination= g.isSessionDone();
    int CurrentSize;
    while (!termination){
            CurrentSize = agents.size();
            for (int j = 0; j < CurrentSize; j = j + 1) {
                agents.at(j)->act(*this);
            }
            termination = g.isSessionDone();
            _cycleCurrNum = _cycleCurrNum + 1;
        }
    json output;
    output["graph"]=this->g.GetEdges();
    output["infected"]=this->ListOfInfectedsNodes;
    ofstream o("output.json");
    o<<output;
cout<<output<<endl; //TODO erase

}

Session::Session(const string &path): g(), treeType(), agents(), InfectedsQueue(), _cycleCurrNum(0), ListOfInfectedsNodes(0) {
    json input_data;
    ifstream jasonIn(path);
    jasonIn >> input_data;
    //list of carry nodes given to update
    vector<int> CarryNodes= {};
    int CarryNode;
    Agent* agent;
    for (auto &elem: input_data["agents"]) {
        if (elem.front() == "C")
            agent= new ContactTracer();
        else {
            CarryNode=elem.at(1);
            agent = new Virus(CarryNode);
            CarryNodes.push_back(CarryNode);
        }
        addAgent(*agent);
        delete agent;
    }
    g.updateGraph(input_data["graph"], CarryNodes);
    initTreeType(input_data["tree"].front());
}

void Session::initTreeType(string tree) {
    if (tree=="M") treeType=MaxRank;
    if (tree == "C") treeType=Cycle;
    if (tree == "R") treeType=Root;
}

int Session::dequeueInfected() {
    if (!InfectedsQueue.empty()) {
        int number = InfectedsQueue.front();
        InfectedsQueue.pop();
        return number;
    }
    return -1; // := queue is empty
}

void Session::enqueueInfected(int number) {
    ListOfInfectedsNodes.push_back(number);
    InfectedsQueue.push(number);
}

TreeType Session::getTreeType() const {
    return treeType;
}

const Graph &Session::getG() const {
    return g;
}

const int Session::get_cycleCurrNum() const {return _cycleCurrNum;}

Graph & Session::getGraphReference() {
    return g;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

//---- Rule of 5

//destructor
Session::~Session(){
    for (Agent* agent:agents) delete agent;
    agents.clear();
    while (!InfectedsQueue.empty()) InfectedsQueue.pop();
    g.clean();
    ListOfInfectedsNodes.clear();
}

//copy constructor
Session::Session(const Session& other): g(other.g),
                                        treeType(other.treeType),
                                        agents(),
                                        InfectedsQueue(other.InfectedsQueue),
                                        _cycleCurrNum(other._cycleCurrNum),
                                        ListOfInfectedsNodes(other.ListOfInfectedsNodes)
{
    for (Agent* agent: other.agents) this->addAgent(*agent);
}

//copy assigment operator
Session & Session:: operator=(const Session& other) {
    if (this != &other) {
    clean();
    copy(other);
}
    return (*this);
}

// move constructor
Session::Session(Session &&other) noexcept: g(other.g),
                                            treeType(other.treeType),
                                            agents(),
                                            InfectedsQueue(other.InfectedsQueue),
                                            _cycleCurrNum(other._cycleCurrNum),
                                            ListOfInfectedsNodes(other.ListOfInfectedsNodes)
{stealAgents(other);}
// move assigment operator
Session& Session::operator=(Session&& other) noexcept {
    if (this!= &other){
        clean();
        _cycleCurrNum=other._cycleCurrNum;
        ListOfInfectedsNodes=other.ListOfInfectedsNodes;
        stealAgents(other);
        g=other.g;
        treeType=other.treeType;
        InfectedsQueue=other.InfectedsQueue;
    }
    return *this;
}
// methodes for Rule of five

void Session:: clean(){
    _cycleCurrNum=0;
    ListOfInfectedsNodes.clear();
    for (Agent* agent:agents) delete agent;
    agents.clear();
    while (!(InfectedsQueue.empty())){
        InfectedsQueue.pop();
    };
    g.clean();
}

void Session::stealAgents(Session& other){
    for(Agent* agent: other.agents){
        agents.push_back(agent);
    }
    other.agents.clear();
}

void Session:: copy(const Session& other) {
        g = other.g;
        treeType = other.treeType;
        for (Agent* agent: other.agents) addAgent(*agent);
    InfectedsQueue= other.InfectedsQueue;
        _cycleCurrNum=other._cycleCurrNum;
    ListOfInfectedsNodes=other.ListOfInfectedsNodes;
    }





