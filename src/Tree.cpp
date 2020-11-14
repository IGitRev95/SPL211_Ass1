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
        othertree = nullptr;
    }
}

void Tree::cloneChildren(const Tree &other) {
    for(Tree* tree : other.children)
    {
        children.push_back(tree->clone());
    }
}

void Tree::addChild( Tree &child) {
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

const Tree & Tree::operator=(const Tree &other) {//TODO: test tree ass oprt
    if(this!=&other) {
        clear();
        node=other.node;
        for(Tree* tree:other.children)
        {
            children.push_back(tree->clone());
        }
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

Tree* Tree::createTree(const Session &session, int rootLabel){
     //CAllBFS

     //MEMORY LEAK OPTION
     vector<vector<int>>* bfsData(session.getG().BFSScan(rootLabel));
     vector<Tree*> nodes_control(session.getG().getNumOfVertices());//gonna get from BFSScan
     for(int i=0;i<nodes_control.size();i=i+1)//nodes initiation
     {
        nodes_control.at(i) = Tree::createNodeTree(session, i);
     }

     for (int i = 0; i < nodes_control.size(); i=i+1)
     {
         if(-1!=bfsData->at(i).at(2))
             nodes_control.at(bfsData->at(i).at(2))->addChild(*nodes_control.at(i));
     }
     Tree* ans(nodes_control.at(rootLabel)->clone());

     for(int i=0;i<nodes_control.size();i=i+1)//nodes initiation
     {
         if(-1==bfsData->at(i).at(2))
          delete nodes_control.at(i);
     }

    delete bfsData;
    return ans;
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
    return 0;
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

}

int CycleTree::getCycle() const {return currCycle;}


////----------------------MaxRankTree

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

MaxRankTree::MaxRankTree(const MaxRankTree &other):Tree(other){}

int MaxRankTree::traceTree() {
    return 0;
}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
////RootTree methods implementation
RootTree::RootTree(int rootLabel):Tree(rootLabel){}
RootTree::RootTree(const RootTree &other):Tree(other) {}
int RootTree::traceTree() {return node;}

Tree * RootTree::clone() const {
    return new RootTree(*this);
}
////---------------------------------