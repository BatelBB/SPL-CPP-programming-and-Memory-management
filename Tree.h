#ifndef TREE_H_
#define TREE_H_


#include <vector>


class Session;


class Tree {
public:
    Tree(int rootLabel);

    virtual ~Tree();


    //Copy Constructor
    Tree(const Tree &other);


    //Copy Assignment
    Tree &operator=(const Tree &other);


    //Move Constructor
    Tree(Tree &&other);


    //Move Assignment
    Tree &operator=(Tree &&other);


    void addChild(const Tree &child);


    int getNode() const;

    std::vector<Tree *> getSubTrees() const;


    virtual Tree *clone() const = 0;


    static Tree *createTree(const Session &session, int rootLabel);


    virtual int traceTree() = 0;

private:
    int node;


    void copy(const int otherNode, const std::vector<Tree *> &otherChildren);


    void clear();


    //allowed to change to protected according to forum post
    //https://www.cs.bgu.ac.il/~spl211/Assignments/Assignment_1Forum?action=show-thread&id=bc900facefe72dfa38374015226c27d9
protected:
    std::vector<Tree *> children;
};


class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual Tree *clone() const;

private:
    int currCycle;
};


class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;
};


class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;
};


#endif

