//
// Created by spl211 on 03/11/2020.
//

#include "include/Session.h"
#include <iostream>
#include <fstream>
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path) {
    json input_data;
    ifstream jasonIn(path);
    jasonIn >> input_data;
    Graph g(input_data["graph"]); //TODO:Need to make a copy constructor or assignment constructor
    //treeType(input_data["tree"]);//TODO:set a tree type
    //TODO: make a method that pulls the agents starting list from json and add to agents field using add_agent
};

