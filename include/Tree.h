#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
using namespace std;
class Graph;
class Session;

class Tree{
public:
    Tree(int rootLabel); // constructor

    // General Tree Methods
    void addChild(const Tree& child);
    const vector<Tree*> getChildren() const;
    const int getRootLabel() const ;
    static Tree* createTree(const Session& session, int rootLabel);
    static Tree* createNodeTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

    //----- Rule of Five/
    Tree(const Tree &other); // copy constructor
    Tree(Tree&& other); // move constructor
    virtual Tree *clone() const = 0;
    virtual ~ Tree(); // destructor
    void clear();
    const Tree& operator=(const Tree& other); // Ass oprt
    Tree& operator=(Tree&& other); // move Ass oprt

protected:
    int node;
    std::vector<Tree*> children;
    void RecursiveCreate(const Session& session,const Graph& bfsgraph);
    void stealChildren(Tree& other);
    void cloneChildren(const Tree& other);
    //const Tree& basicAssigment(const Tree& other);//-optional

};

class CycleTree: public Tree{
public:

    CycleTree(int rootLabel, int currCycle); // constructor
    virtual int traceTree();
    virtual Tree *clone() const ;
    int getCycle()const ;
    int traceTreeRecursive(int cycleCounter);

private:

    int currCycle;

};

class MaxRankTree: public Tree{
public:

    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree *clone() const ;
    std::vector<int>* maxRankWinRec(int depth);

};

class RootTree: public Tree{
public:

    RootTree(int rootLabel); // constructor
    virtual int traceTree();
    virtual Tree *clone() const ;

};

#endif
