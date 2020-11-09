//
// Created by spl211 on 03/11/2020.
//

#include "include/Tree.h"
#include <queue>

using namespace std;

Tree::Tree(int rootLabel):node(rootLabel),children(){}

Tree::Tree(int node, const vector<Tree *> &children) : node(node), children(children) {}

void Tree::addChild(const Tree &child) {
    this->children.push_back(child.clone());
}

Tree::~Tree() {
    for(Tree* childtree:children)
    {
            delete childtree;
    }
}

 Tree* Tree::createTree(const Session &session, int rootLabel){
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
             return new CycleTree(rootLabel,session.get_cycleCurrNum());//Should be deleted by CT
         }
     }

}
//
////RootTree methods implementation
//RootTree::RootTree(int rootLabel):Tree(rootLabel){}
//
//int RootTree::traceTree() {return node;}
////---------------------------------

CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

CycleTree::CycleTree(const CycleTree &cT):Tree(cT.node,cT.children),currCycle(cT.currCycle) {}

Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

CycleTree::~Tree() {
    for(Tree* childtree:children)
    {
        delete childtree;
    }
}
//int CycleTree::getCycle() const {return currCycle;}