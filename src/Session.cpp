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
    bool terminate= g.SessionDone();
    int CurrentSize;
    if (!terminate)
        do {
            _cycleCurrNum = _cycleCurrNum + 1;
            CurrentSize = agents.size();
            for (int j = 0; j < CurrentSize; j = j + 1) {
                agents.at(j)->act(*this);
            }
            terminate = g.SessionDone();
        } while (!terminate);
    json output;
    output["graph"]=this->g.GetEdges();
    output["infected"]=this->numofinfecteds;
    ofstream o("output.json");
    o<<output;
cout<<output<<endl;

}

Session::Session(const string &path): g(), treeType(),agents(),infecteds(),_cycleCurrNum(0) {
    json input_data;
    ifstream jasonIn(path);
    jasonIn >> input_data;
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
    g.updateMatrix(input_data["graph"], CarryNodes);
    string tree= input_data["tree"].front();
    if (tree=="M") treeType=MaxRank;
    if (tree == "C") treeType=Cycle;
    if (tree == "R") treeType=Root;
    }
int Session::dequeueInfected() {
    if (!infecteds.empty()) {
        int number = infecteds.front();
        infecteds.pop();
        return number;
    }
    return -1;
}
void Session::enqueueInfected(int number) {
    numofinfecteds.push_back(number);
    infecteds.push(number);
}
TreeType Session::getTreeType() const {
    return treeType;
}
//--------------------------------------------------
        void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());}
 //--------------------------------------------------
//    bool Session::isInfectedQueueEmptey() {
//        return infecteds.empty();
//}
 //--------------------------------------------------
 int Session::get_cycleCurrNum() const {return _cycleCurrNum;}
//---------------------------------------------------
 Graph & Session::getGraphReference() {
    return g;
}
//--------------------------------------------------
void Session::setGraph(const Graph &graph) {
    g = graph;
}
 //---------------------------------

//---- Rule of 5
//destructor
Session::~Session(){
    for (Agent* agent:agents) delete agent;
    agents.clear();
    while (!infecteds.empty()) infecteds.pop();
    g.clean();
    numofinfecteds.clear();
    cout<<"destructor session"<<endl;
}
//copy constructor
Session::Session(const Session& other): g(other.g),
treeType(other.treeType),
agents(),
infecteds(other.infecteds),
_cycleCurrNum(other._cycleCurrNum),
numofinfecteds(other.numofinfecteds)
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
Session::Session(Session &&other) noexcept: g(move(other.g)),
infecteds(move(other.infecteds)),
_cycleCurrNum(other._cycleCurrNum),
agents(move(other.agents)),
treeType(other.treeType),
numofinfecteds(move(other.numofinfecteds))
{other.agents.clear();}
// move assigment operator
Session& Session::operator=(Session&& other) noexcept {
    if (this!= &other){
        clean();
        _cycleCurrNum=other._cycleCurrNum;
        numofinfecteds=other.numofinfecteds;
        for (int i=0; i<agents.size(); i++) {
            *agents.at(i) = *other.agents.at(i);
            other.agents.at(i)= nullptr;
        }
        g=(move(other.g));
        treeType=other.treeType;
        infecteds=(move(infecteds));
    }
    return *this;
}

void Session:: clean(){
    _cycleCurrNum=0;
    numofinfecteds.clear();
    for (Agent* agent:agents) delete agent;
    agents.clear();
    while (!(infecteds.empty())){
        infecteds.pop();
    };
    g.clean();
}


    void Session:: copy(const Session& other) {
        g = other.g;
        numofinfecteds=other.numofinfecteds;
        treeType = other.treeType;
        for (Agent* agent: other.agents) addAgent(*agent);
        infecteds= other.infecteds;
    }

const Graph &Session::getG() const {
    return g;
}




