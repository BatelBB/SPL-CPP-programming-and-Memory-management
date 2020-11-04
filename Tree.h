#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session{};

class Tree{
public:
    //constructor to tree. 
    //TODO: destructor to the tree
    Tree(int rootLabel);
    //add a child to the tree, a reference
    void addChild(const Tree& child);
    void addChild(Tree* child);        //We added from the screenshot
    const Tree& getChild(int) const;   //We added from the screenshot

//from forum - returns the reference to the tree that is being created.
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
protected:
    //represents the node of the current tree?
    int node;
    
    //I think it's used to set the cildren of the tree, not sure of which method.
    std::vector<Tree*> children;
};
//with this tree the viruse knows where to go
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    //represents the current cycle that the work flow is in right now
    int currCycle;
};
//returns the MaxRankTree after the contactTracer did what it had to do
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};
//returnes the RootTree of the tree that the contactTracer did the BFS search on
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
