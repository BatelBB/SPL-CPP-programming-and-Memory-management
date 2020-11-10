#ifndef AGENT_H_
	#define AGENT_H_
	

	#include <vector>
	#include "Session.h"
	

	class Agent{
	public:
	    Agent(Session& session);
	    
	    virtual void act()=0;
	

	    //pure virtual method for copy constructor
	    virtual Agent* clone() const =0;
	

	    virtual int getNodeInd() const =0;
	protected:
	    Session& session;
	};
	

	class ContactTracer: public Agent{
	public:
	    ContactTracer(Session& session);
	    
	    virtual void act();
	

	    virtual Agent* clone() const;
	

	//returns -1
	    virtual int getNodeInd() const;
	};
	

	

	class Virus: public Agent{
	public:
	    Virus(int nodeInd, Session& session);
	    
	    virtual void act();
	

	    virtual Agent* clone() const;
	

	    virtual int getNodeInd() const;
	

	private:
	    const int nodeInd;
	};
	

	#endif

