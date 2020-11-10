#ifndef TREE_H_
	#define TREE_H_
	

	#include <vector>
	

	class Session;
	

	class Tree{
	public:
	    Tree(int rootLabel);
	    void addChild(const Tree& child);
	

	    int getNode() const;
	

	    //might not be okay to add public getter for children
	    std::vector<Tree*> getChildren() const;
	    //pure virtual method for copy constructor
	    virtual Tree* clone() const =0;
	

	

	    static Tree* createTree(const Session& session, int rootLabel);
	    virtual int traceTree()=0;
	private:
	    int node;
	

	//allowed to change to protected according to forum post
	//https://www.cs.bgu.ac.il/~spl211/Assignments/Assignment_1Forum?action=show-thread&id=bc900facefe72dfa38374015226c27d9
	protected:
	    std::vector<Tree*> children;
	};
	

	class CycleTree: public Tree{
	public:
	    CycleTree(int rootLabel, int currCycle);
	    virtual int traceTree();
	    virtual Tree* clone() const;
	

	private:
	    int currCycle;
	};
	

	class MaxRankTree: public Tree{
	public:
	    MaxRankTree(int rootLabel);
	    virtual int traceTree();
	

	    virtual Tree* clone() const;
	

	private:
	    int maxRank;
	};
	

	class RootTree: public Tree{
	public:
	    RootTree(int rootLabel);
	    virtual int traceTree();
	    virtual Tree* clone() const;
	};
	

	#endif

