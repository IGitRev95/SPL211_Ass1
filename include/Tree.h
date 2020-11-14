#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Session;

class Tree{
public:
    Tree(int rootLabel); // constructor

    //Tree(int node, const std::vector<Tree *> &children);

    void addChild(const Tree& child);
    void addChild(Tree& child);

    static Tree* createTree(const Session& session, int rootLabel);
    static Tree* createNodeTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

    //----- Rule of Five/
    Tree(const Tree &other); // copy constructor
    Tree(Tree&& other); // move constructor
    virtual Tree *clone() const = 0;
    virtual ~ Tree(); // destructor
    void clear();
    virtual const Tree& operator=(const Tree& other); // Ass oprt
    virtual Tree& operator=(Tree&& other); // move Ass oprt
protected:
    int node;
    std::vector<Tree*> children;

    void stealChildren(Tree& other);
    void cloneChildren(const Tree& other);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle); // constructor
    CycleTree(const CycleTree& other); // copy constructor
    CycleTree(CycleTree&& other); // move constructor
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ CycleTree() = default; // destructor
    virtual const CycleTree& operator=(const CycleTree& other); // Ass oprt
    virtual CycleTree& operator=(CycleTree&& other); // move Ass oprt
    int getCycle()const ;


private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree& other); // copy constructor
    MaxRankTree(MaxRankTree&& other) = default; // move constructor
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ MaxRankTree() = default; // destructor
    virtual const MaxRankTree& operator=(const MaxRankTree& other) = default; // Ass oprt
    virtual MaxRankTree& operator=(MaxRankTree&& other)=default; // move Ass oprt
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel); // constructor
    RootTree(const RootTree& other); // copy constructor
    RootTree(RootTree&& other) = default; // move constructor
    virtual int traceTree();
    virtual Tree *clone() const ;
    virtual ~ RootTree() = default; // destructor
    virtual const RootTree& operator=(const RootTree& other) = default;// Ass oprt
    virtual RootTree& operator=(RootTree&& other)=default; // move Ass oprt
};

#endif
