//
// Created by spl211 on 03/11/2020.
//
//#include <iostream>
#include <queue>
#include "include/Tree.h"

using namespace std;

////Tree-----------

Tree::Tree(int rootLabel):node(rootLabel),children(){}

//Tree::Tree(int node, const vector<Tree *> &children) : node(node), children(children) {}

void Tree::addChild(const Tree &child) {
    this->children.push_back(child.clone());
}

const vector<Tree*> Tree:: getChildren(){return this->children;}

const int Tree:: getRootLabel(){return this->node;}

Tree::Tree(const Tree &other): Tree(other.node){
    cloneChildren(other);
}
// move constructor
Tree::Tree(Tree &&other):Tree(other.node) { //TODO: test Tree move con
    stealChildren(other);
}

void Tree::stealChildren(Tree &other) {
    for(Tree* othertree: other.children)
    {
        children.push_back(othertree);
    }
    other.children.clear();
}

void Tree::cloneChildren(const Tree &other) {
    for(Tree* tree : other.children)
    {
        addChild(*tree);
        // children.push_back(tree->clone());
    }
}

void Tree::addRealChild(Tree &child) {
    this->children.push_back(&child);
}

Tree::~Tree() {
    if(!children.empty())
        clear();
    //cout<<"Tree of node: "<<node<<" is clear"<<endl;
}

void Tree::clear() {
    for(Tree* childTree:children)
    {
        delete childTree;
    }
    children.clear();
}

const Tree & Tree::operator=(const Tree &other) {
    if(this!=&other) {
        clear();
        node=other.node;
        cloneChildren(other);
    }
    return *this;
}

Tree & Tree::operator=(Tree &&other) {//TODO: Test Tree move Ass oprt
    if(this!=&other) {
        clear();
        node=other.node;
        stealChildren(other);
    }
    return *this;
}

void Tree::RecursiveCreate(const Session& session,const Graph& bfsgraph) {
    vector<int> EdgesOfNode= bfsgraph.getEdgesOf(this->node);
    Tree* child;
    for (int i=0;i<EdgesOfNode.size();i++) {
        if (i != node && EdgesOfNode[i] == 1) {
        child = createNodeTree(session, i);
        (*child).RecursiveCreate(session,bfsgraph);
        addChild(*child);
        delete child;
    }
    }
}

Tree* Tree::createTree(const Session &session, int rootLabel){
    //CAllBFS
    Tree* output= createNodeTree(session,rootLabel);
    //MEMORY LEAK OPTION
    Graph* bfsgraph(session.getG().BFSScan(rootLabel));
    (*output).RecursiveCreate(session,*bfsgraph);
    delete bfsgraph;
    return output;
}

Tree * Tree::createNodeTree(const Session &session, int rootLabel) {
    switch (session.getTreeType()) {
        case Root:
        {
            return new RootTree(rootLabel);//Should be deleted by CT
        }
        case MaxRank:
        {
            return new MaxRankTree(rootLabel);//Should be deleted by CT
        }
        case Cycle:
        {
            return new CycleTree(rootLabel, session.get_cycleCurrNum());//Should be deleted by CT
        }
    }
}

////CycleTree-------------


CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

CycleTree::CycleTree(const CycleTree &other): Tree(other), currCycle(other.currCycle) {}

CycleTree::CycleTree(CycleTree &&other):CycleTree(other.node,other.currCycle){
    stealChildren(other);
}

int CycleTree::traceTree() {
    return traceTreeRecursive(currCycle);
}

int CycleTree::traceTreeRecursive(int cycleCounter){
    if(cycleCounter==0 || children.empty())
        return node;
    else{
        CycleTree* child= static_cast<CycleTree *>(children.front());
        return child->traceTreeRecursive(cycleCounter-1);
    }
}

Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

const CycleTree & CycleTree::operator=(const CycleTree &other) {
    if(this!=&other)
    {
        clear();
        node=other.node;
        currCycle=other.currCycle;
        cloneChildren(other);
    }
    return *this;
}

CycleTree & CycleTree::operator=(CycleTree &&other) {
    if(this!=&other)
    {
        clear();
        node=other.node;
        currCycle=other.currCycle;
        stealChildren(other);
    }
    return *this;
}

int CycleTree::getCycle() const {return currCycle;}


////----------------------MaxRankTree

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

MaxRankTree::MaxRankTree(const MaxRankTree &other):Tree(other){}

int MaxRankTree::traceTree() {
    vector<int>* maxRankNodeDetails= maxRankWinRec(0);
    const int nodeIndex(2);
    int ans=maxRankNodeDetails->at(nodeIndex);
    delete maxRankNodeDetails;
    return ans;
}

std::vector<int> * MaxRankTree::maxRankWinRec(int currDepth) {
    /*
     * every sub tree returns a triplet, as a vector,
     * of values of the max rank node in its self sourced tree.
     * the triplet structure is as foolows:
     * [0]:=Rank , [1]:=Depth, [2]:=node
    */
    vector<int>* winner = new std::vector<int>();
    winner->push_back(children.size());
    winner->push_back(currDepth);
    winner->push_back(node);
    int nodeRank(0);
    int nodeDepth(1);
    int nodeIndex(2);
    for(Tree* child:children){

        MaxRankTree* maxRankChild=static_cast<MaxRankTree*>(child);
        vector<int>* candidate= maxRankChild->maxRankWinRec(currDepth + 1);
        if (candidate->at(nodeRank) > winner->at(nodeRank)){
            *winner=*candidate;
        }
        else if (candidate->at(nodeRank) == winner->at(nodeRank)){
                if (candidate->at(nodeDepth) < winner->at(nodeDepth)){
                    *winner=*candidate;
                } else if (candidate->at(nodeDepth) == winner->at(nodeDepth)){
                            if (candidate->at(nodeIndex) < winner->at(nodeIndex)){
                                *winner=*candidate;
                            }
                        }
        }
        delete candidate;
    }
    return winner;
}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

const MaxRankTree & MaxRankTree::operator=(const MaxRankTree &other) {
    if(this!=&other) {
        clear();
        node=other.node;
        cloneChildren(other);
    }
    return *this;
}

MaxRankTree & MaxRankTree::operator=(MaxRankTree &&other) {
    if(this!=&other) {
        clear();
        node=other.node;
        stealChildren(other);
    }
    return *this;
}

////RootTree methods implementation

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

RootTree::RootTree(const RootTree &other):Tree(other) {}

int RootTree::traceTree() {return node;}

Tree * RootTree::clone() const {
    return new RootTree(*this);
}

const RootTree & RootTree::operator=(const RootTree &other) {
    if(this!=&other) {
        clear();
        node=other.node;
        cloneChildren(other);
    }
    return *this;
}

RootTree & RootTree::operator=(RootTree &&other) {
    if(this!=&other) {
        clear();
        node=other.node;
        stealChildren(other);
    }
    return *this;
}
////---------------------------------