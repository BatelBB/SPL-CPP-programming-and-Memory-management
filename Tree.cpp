#include <iostream>
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
    return 0;
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
    return 0;
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
    return 0;
}

Tree *RootTree::clone() const
{
    return new RootTree(*this);
}
