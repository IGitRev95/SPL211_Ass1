#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <queue>
#include "Agent.h"
class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    void simulate();
    Session(const std::string& path); //implemented but need to check efficiency
    void addAgent(const Agent& agent);// implemented
    void setGraph(const Graph& graph); // why we need this function
    void enqueueInfected(int); // implemented
    int dequeueInfected(); // implemented
    TreeType getTreeType() const; // implemented
    Session(const Session &other); // copy constructor
    Session & operator=(const Session& other); // copy assignment operator
    Session(Session&& other) noexcept; // move constructor
    Session& operator=(Session&& other) noexcept; // move assigment operator
    void copy(const Session& other);
    bool isInfectedQueueEmptey();//implemented

    int get_cycleCurrNum() const ;//implemented
    const Graph &getG() const;



//     Graph& getGraph() ;

    Graph* getPointerGraph() ;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infecteds;
    int _cycleCurrNum;
};

#endif
