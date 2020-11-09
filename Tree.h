#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree
{
public:
    //constructor
    Tree(int rootLabel);

    //add a child to the node, a reference - uses the queue data structur, uses the one dimention vector children, sends a clone of the child.
    void addChild(const Tree &child);

    //destructor
    virtual ~Tree();

    //returns the node in the protected field.
    int getCurrNode() const;

    //virtual abstract method - used to clone the tree.
    virtual Tree *clone() const = 0;

    //returns the reference to the tree that is being created - depends on the type of the tree.
    static Tree *createTree(const Session &session, int rootLabel);

    //an abstract method
    virtual int traceTree() = 0;

    //returns a vector with the children of the current node
    std::vector<Tree *> getNodeChildren() const;

private:
    //represents the node of the current tree
    int node;
protected:
    //Using the queue to add children
    std::vector<Tree *> children;
};

//with this tree the virus knows where to go
class CycleTree : public Tree
{
public:
    //constructor
    CycleTree(int rootLabel, int currCycle);

    //returns the index of the node in the graph
    virtual int traceTree();

    //virtual clone method - clones the tree - (copy constructor)
    virtual Tree *clone() const;

private:
    //represents the current cycle that the work flow is in right now
    int currCycle;
};
//returns the MaxRankTree after the contactTracer did what it had to do
class MaxRankTree : public Tree
{
public:
    //constructor
    MaxRankTree(int rootLabel);

    //virtual method - return the index of the node in the graph
    virtual int traceTree();

    //virtual clone method - clones the tree - (copy constructor)
    virtual Tree *clone() const;

private:
    int maxTree;
};

//returns the RootTree of the tree that the contactTracer did the BFS search on
class RootTree : public Tree
{
public:
    //constructor
    RootTree(int rootLabel);

    //virtual method - return the index of the node in the graph
    virtual int traceTree();

    //virtual clone method - clones the tree - (copy constructor)
    virtual Tree *clone() const;
};

#endif
