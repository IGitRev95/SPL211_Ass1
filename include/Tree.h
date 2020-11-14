#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Session;

class Tree{
public:
    Tree(int rootLabel);

    //Tree(int node, const std::vector<Tree *> &children);

    void addChild(const Tree& child);
    void addChild( Tree& child);


    static Tree* createTree(const Session& session, int rootLabel);
    static Tree* createNodeTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

    //----- Rule of Five/
    Tree(const Tree &other); //copy constructor
    virtual Tree *clone() const = 0;
    virtual ~ Tree();
    void clear();
    virtual const Tree& operator=(const Tree& other);//Ass oprt
protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree& other);
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ CycleTree() = default;
    virtual const CycleTree& operator=(const CycleTree& other);//Ass oprt
    int getCycle()const ;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);

    //copy constructor
    MaxRankTree(const MaxRankTree& other);
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ MaxRankTree() = default;
    virtual const MaxRankTree& operator=(const MaxRankTree& other) = default;

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    //copy constructor
    RootTree(const RootTree& other);
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ RootTree() = default;
    virtual const RootTree& operator=(const RootTree& other) = default;
};

#endif
