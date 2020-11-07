#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
using namespace std;
class Agent {
public:
    Agent();
    bool getMakeChanges() const;
   // virtual void act(Session &session)=0;
    virtual Agent *clone() const = 0;

protected:
    bool MakeChanges;
};
class ContactTracer: public Agent{
public:
    ContactTracer();
    
   // virtual void act(Session& session);
    Agent* clone() const override ;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
   // virtual void act(Session& session);
    Agent* clone() const override ;
    int getNumber() const;
private:
    const int nodeInd;
};


#endif
