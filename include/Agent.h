#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
// forward declaration
class Session;
class Agent{
public:
    Agent();
    virtual ~Agent();
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;

protected:
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
