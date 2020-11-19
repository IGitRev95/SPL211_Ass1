//
// Created by spl211 on 03/11/2020.
//
//#include <iostream>
#include <queue>
#include "include/Tree.h"

using namespace std;

////Tree-----------

Tree::Tree(int rootLabel):node(rootLabel),children(){}

void Tree::addChild(const Tree &child) {
    this->children.push_back(child.clone());
}

const vector<Tree*> Tree:: getChildren() const {return this->children;}

const int Tree:: getRootLabel() const {return this->node;}

//returns pointer to a BFS Tree
Tree* Tree::createTree(const Session &session, int rootLabel){
    Tree* output= createNodeTree(session,rootLabel); // create tree of rootlabel node
    // calling BFS Scan of the graph and returns the BFS tree represented as graph
    Graph* bfsgraph(session.getG().BFSScan(rootLabel));
    //make Bfs tree using Bfs tree as a graph and rootlabel
    (*output).RecursiveCreate(session,*bfsgraph);
    delete bfsgraph;
    return output;
}
// create tree of rootlable node
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
    return nullptr;
}
//copy constructor
Tree::Tree(const Tree &other): Tree(other.node){
    cloneChildren(other);
}
// move constructor
Tree::Tree(Tree &&other):Tree(other.node) {
    stealChildren(other);
}
//destructor
Tree::~Tree() {
    if(!children.empty())
        clear();
    //cout<<"Tree of node: "<<node<<" is clear"<<endl;
}
//delete children
void Tree::clear() {
    for(Tree* childTree:children)
    {
        delete childTree;
    }
    children.clear();
}
// copy assigment operator
const Tree & Tree::operator=(const Tree &other) {
    if(this!=&other) {
        clear();
        node=other.node;
        cloneChildren(other);
    }
    return *this;
}
// move assigment operator
Tree & Tree::operator=(Tree &&other) {
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
    for (unsigned int i=0;i<EdgesOfNode.size();i++) {
        if (i != (unsigned int)node && EdgesOfNode[i] == 1) {
            child = createNodeTree(session, i);
            (*child).RecursiveCreate(session,bfsgraph);
            addChild(*child);
            delete child;
        }
    }
}
//steal adress of children from other
void Tree::stealChildren(Tree &other) {
    for(Tree* othertree: other.children)
    {
        children.push_back(othertree);
    }
    other.children.clear();
}

void Tree::cloneChildren(const Tree &other) {
    for(Tree* tree : other.children) {
        addChild(*tree);
        // children.push_back(tree->clone());
    }
}

////CycleTree-------------
//constructor
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

int CycleTree::traceTree() {
    return traceTreeRecursive(currCycle);
}

Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::getCycle() const {return currCycle;}

int CycleTree::traceTreeRecursive(int cycleCounter){
    if(cycleCounter==0 || children.empty())
        return node;
    else{
        CycleTree* child= static_cast<CycleTree *>(children.front());
        return child->traceTreeRecursive(cycleCounter-1);
    }
}


////----------------------MaxRankTree

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

int MaxRankTree::traceTree() {
    vector<int>* maxRankNodeDetails= maxRankWinRec(0);
    const int nodeIndex(2);
    int ans=maxRankNodeDetails->at(nodeIndex);
    delete maxRankNodeDetails;
    return ans;
}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

std::vector<int> * MaxRankTree::maxRankWinRec(int currDepth) {
    /*
     * every sub tree returns a triplet, as a vector,
     * of values of the max rank node in its self sourced tree.
     * the triplet structure is as foolows:
     * [0]:=Rank , [1]:=Depth, [2]:=node
    */
    vector<int>* winner = new std::vector<int>();
    //current node values
    winner->push_back(children.size());
    winner->push_back(currDepth);
    winner->push_back(node);
    int nodeRank(0);
    int nodeDepth(1);
    int nodeIndex(2);
    for(Tree* child:children){
        MaxRankTree* maxRankChild=static_cast<MaxRankTree*>(child);
        vector<int>* candidate= maxRankChild->maxRankWinRec(currDepth + 1);
        //check for most Rank
        if (candidate->at(nodeRank) > winner->at(nodeRank)){
            *winner=*candidate;
        }
        else if (candidate->at(nodeRank) == winner->at(nodeRank)){
            //check smaller depth
            if (candidate->at(nodeDepth) < winner->at(nodeDepth)){
                *winner=*candidate;
            } else if (candidate->at(nodeDepth) == winner->at(nodeDepth)){
                //check for smaller index
                if (candidate->at(nodeIndex) < winner->at(nodeIndex)){
                    *winner=*candidate;
                }
            }
        }
        delete candidate;
    }
    return winner;
}

////RootTree methods implementation

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

int RootTree::traceTree() {return node;}

Tree * RootTree::clone() const {
    return new RootTree(*this);
}

////---------------------------------