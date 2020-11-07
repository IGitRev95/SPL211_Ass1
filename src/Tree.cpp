//
// Created by spl211 on 03/11/2020.
//

#include "include/Tree.h"

using namespace std;

Tree::Tree(int node, const vector<Tree *> &children) : node(node), children(children) {}

//Tree::Tree(int rootLabel)//BFS
//{
//    std::vector<std::vector<int>> verticesInfo;
//}

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

//RootTree methods implementation
RootTree::RootTree(int rootLabel):Tree(rootLabel){}

int RootTree::traceTree() {return node;}
//---------------------------------

