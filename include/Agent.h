#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
// forward declaration
using namespace std;
class Session;
class Agent{
public:
    Agent();

    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;
    bool getMakeChanges() const;

protected:
    bool MakeChanges;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    
    virtual void act(Session& session);
    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual void act(Session& session);
    virtual Agent* clone() const;
    int getNumber() const;
private:
    const int nodeInd;
};


#endif
