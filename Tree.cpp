#include <vector>
	#include "Tree.h"
	#include "Session.h"
	

	using namespace std;
	

	Tree* Tree::createTree(const Session& session, int rootLabel)
	{
	    switch (session.getTreeType())
	    {
	    case MaxRank:
	        return new MaxRankTree(rootLabel);
	    
	    case Cycle:
	        return new CycleTree(rootLabel, session.getCurrentCycle());
	

	    case Root:
	        return new RootTree(rootLabel);
	    }
	}
	

	Tree::Tree(int rootLabel):node(rootLabel){}
	

	

	CycleTree::CycleTree(int rootLabel,int currCycle):Tree(rootLabel),currCycle(currCycle) {}
	

	MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
	

	RootTree::RootTree(int rootLabel):Tree(rootLabel) {}
	

	

	int CycleTree::traceTree()
	{
	    int depth = 0;
	    bool finished = false;
	    Tree* currentTree = this;
	

	    while (!finished)
	    {
	        if (currCycle ==depth || !currentTree->getChildren().empty())
	        {
	            return currentTree->getNode();
	        }
	

	        currentTree = currentTree->getChildren()[0];
	        depth += 1;
	    }
	}
	

	

	int MaxRankTree::traceTree()
	{
	    int maxRank=-1;
	    int maxNode=-1;
	    // Create a queue for BFS 
	    queue<Tree *> BFSqueue; 
	  
	    BFSqueue.push(this); 
	

	    
	  
	    //This is gonna be a bitch to debug lol
	    while(!BFSqueue.empty()) 
	    { 
	        // Dequeue a vertex from queue 
	        Tree* currentTree = BFSqueue.front(); 
	        BFSqueue.pop();
	

	        vector<Tree*> currentChildren = currentTree->getChildren();
	

	        int currentRank = currentChildren.size();
	        if (currentRank > maxRank)
	        {
	            maxRank = currentRank;
	            maxNode = currentTree->getNode();
	

	        }
	

	        for (int i=0; i<currentChildren.size() ; i++)
	        {
	            BFSqueue.push(currentChildren[i]);
	        } 
	    }
	

	    return maxNode;
	

	}
	

	

	int RootTree::traceTree()
	{
	    return getNode();
	}
	

	Tree* CycleTree::clone() const
	{
	    return new CycleTree(*this);
	}
	

	Tree* MaxRankTree::clone() const
	{
	    return new MaxRankTree(*this);
	}
	

	Tree* RootTree::clone() const
	{
	    return new RootTree(*this);
	}
	

	

	void Tree::addChild(const Tree& child)
	{
	    children.push_back(child.clone());
	}
	

	

	int Tree::getNode() const
	{
	    return node;
	}
	

	vector<Tree*> Tree::getChildren() const
	{
	    return children;
	}

