#include <iostream>
#include "include/Session.h"

using namespace std;
Session foo(Session session);
int main(int argc, char** argv){
//    if(argc != 3){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }

    Session sess5= Session(argv[1]);
    Session sess4= Session(argv[1]);
    sess4.getGraphReference().disconnect(0);
    sess4=sess5;
    sess4.simulate();

    return 0;

}

Session foo(Session session){
    Session sesstry(session);
    sesstry.clean();
    return sesstry;
}

