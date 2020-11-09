#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
using namespace std;
class Session;

class Agent {
public:
    virtual void act(Session &session)=0;
    virtual Agent *clone() const = 0;
    Agent();
    bool getMakeChanges() const;

protected:
    bool MakeChanges;
};
class ContactTracer: public Agent{
public:
    virtual void act(Session& session);

    ContactTracer();
    Agent* clone() const override;
};


class Virus: public Agent{
public:
    virtual void act(Session& session);
    Virus(int nodeInd);
    Agent* clone() const override ;
    int getNumber() const;
private:
    const int nodeInd;
};


#endif
