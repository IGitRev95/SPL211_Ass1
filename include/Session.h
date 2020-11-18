#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "Agent.h"

class Graph;
class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    void simulate();
    Session(const std::string& path);
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    const int get_cycleCurrNum() const ;
    Graph & getGraphReference();
    const Graph &getG() const;

    // Rule of Five
    virtual ~ Session(); // destructor
    Session(const Session &other); // copy constructor
    Session & operator=(const Session& other); // copy assignment operator
    Session(Session&& other) noexcept; // move constructor
    Session& operator=(Session&& other) noexcept; // move assigment operator
    void clean();





private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> InfectedsQueue;
    int _cycleCurrNum;
    std::vector<int> ListOfInfectedsNodes;
    void stealAgents(Session& other);
    void copy(const Session& other);
    void initTreeType(string tree);
};

#endif
