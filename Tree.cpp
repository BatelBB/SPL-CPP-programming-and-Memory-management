#include <vector>
#include "Tree.h"
#include "Session.h"

Tree::Tree(int rootLabel) : node(rootLabel)
{
}

void Tree::addChild(const Tree &child)
{
    children.push_back(child.clone());
}

int Tree::getCurrNode() const
{
    return node;
}

Tree *Tree::createTree(const Session &session, int rootLabel)
{
    switch (session.getTreeType())
    {
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Cycle:
            return new CycleTree(rootLabel, session.getCurrCycleInd());
        case Root:
            return new RootTree(rootLabel);
    }
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle)
{
}

int CycleTree::traceTree()
{
    int treeDepth = 0;
    bool isDone = false;
    Tree *currTree = this;

    while (!isDone){
        if(currCycle == treeDepth || !currTree -> getNodeChildren().empty()){
            return currTree -> getCurrNode();
        }
        currTree = currTree -> getNodeChildren()[0];
        treeDepth += 1;
    }
}

Tree *CycleTree::clone() const
{
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel)
{
}
int MaxRankTree::traceTree()
{
    int treeMax =-1;
    int nodeMax =-1;
    std::queue<Tree *> QueueBFS;

    QueueBFS.push(this);

    while(!QueueBFS.empty()){
        Tree* currTree = QueueBFS.front();
        QueueBFS.pop();

        std::vector<Tree*> currNodeChildren = currTree -> getNodeChildren();

        int currRank = currNodeChildren.size();
        if(currRank > treeMax){
            treeMax = currRank;
            nodeMax = currTree -> getCurrNode();
        }
        for (int i=0; i<currNodeChildren.size(); i++){
            QueueBFS.push(currNodeChildren[i]);
        }
    }
    return nodeMax;
}

Tree *MaxRankTree::clone() const
{
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel)
{
}
int RootTree::traceTree()
{
    return getCurrNode();
}

Tree *RootTree::clone() const
{
    return new RootTree(*this);
}

std::vector<Tree *> Tree::getNodeChildren() const {
    return children;
}
