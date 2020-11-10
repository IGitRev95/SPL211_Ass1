#include <iostream>
#include "include/Session.h"

using namespace std;

int main(int argc, char** argv){
//    if(argc != 2){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
    Session* sess= new Session(argv[1]);
    Session* sess2(new Session(argv[1]));
    delete sess;
    (*sess2).simulate();//TODO:remove from note for simulation programing
    return 0;
}
