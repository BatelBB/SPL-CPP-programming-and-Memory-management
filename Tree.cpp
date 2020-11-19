#include <vector>
#include "Tree.h"
#include "Session.h"

Tree::Tree(int rootLabel) : node(rootLabel), children(std::vector<Tree *>()) {}

Tree::~Tree() {
    clear();
}

void Tree::clear() {
    for (Tree *child : children)
        if (child) {
            delete child;
        }

    children.clear();
}

Tree::Tree(const Tree &other) : Tree(other.node) {
    copy(other.node, other.children);
}

void Tree::copy(const int otherNode, const std::vector<Tree *> &otherChildren) {
    node = otherNode;
    for (auto &child : otherChildren) {
        addChild(*child);
    }
}

Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        copy(other.node, other.children);
    }
    return *this;
}

Tree::Tree(Tree &&other) : node(other.node), children(move(other.children)) {
    other.node = -1;
}

Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        node = other.node;
        children = move(other.children);

        other.node = -1;
    }

    return *this;
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

int Tree::getNode() const {
    return node;
}

std::vector<Tree *> Tree::getSubTrees() const {
    return children;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    switch (session.getTreeType()) {
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Cycle:
            return new CycleTree(rootLabel, session.getCurrCycle());

        case Root:
            return new RootTree(rootLabel);

        default:
            return new RootTree(rootLabel);
    }
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    int treeDepth = 0;
    Tree *currTree = this;

    while (true) {
        if (currCycle == treeDepth || currTree->getSubTrees().empty()) {
            return currTree->getNode();
        }

        currTree = currTree->getSubTrees()[0];
        treeDepth = treeDepth + 1;
    }
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

int MaxRankTree::traceTree() {
    int nodeMaxRank = -1;
    int maxNode = -1;


    std::queue<Tree *> RankQueue;

    RankQueue.push(this);

    while (!RankQueue.empty()) {
        Tree *currTree = RankQueue.front();
        RankQueue.pop();

        std::vector<Tree *> currChildren = currTree->getSubTrees();

        int currRank = currChildren.size();
        if (currRank > nodeMaxRank) {
            nodeMaxRank = currRank;
            maxNode = currTree->getNode();
        }
        for (int i = 0; i < currRank; i++) {
            RankQueue.push(currChildren[i]);
        }
    }

    return maxNode;
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return getNode();
}



