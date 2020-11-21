#include <vector>
#include "Tree.h"
#include "Session.h"

//constructor
Tree::Tree(int rootLabel) : node(rootLabel), children(std::vector<Tree *>()) {}

//destructor
Tree::~Tree() {
    clear();
}

/*clear method to used by the destructor
    checks if the child pointer isn't null, if it's not null then deletes the children of the tree.
 */
void Tree::clear() {
    for (Tree *child : children)
        //checks if the pointer isn't null
        if (child) {
            delete child;
        }
    //the vector method clear()
    children.clear();
}

//copy constructor
Tree::Tree(const Tree &other) : Tree(other.node) {
    copy(other.node, other.children);
}

//copy constructor
void Tree::copy(const int otherNode, const std::vector<Tree *> &otherChildren) {
    node = otherNode;
    //uses the addChild method to create a new pointer for every object
    for (auto &child : otherChildren) {
        addChild(*child);
    }
}

/*copy assignment operator
   returns the object that is assigned
 */
Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        copy(other.node, other.children);
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&other) : node(other.node), children(move(other.children)) {
    other.node = -1;
}

//move assignment operator
Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        node = other.node;
        children = move(other.children);

        other.node = -1;
    }

    return *this;
}

//addChild method - pushes into the children vector the clone of the child reference
void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

//getter - returns the node when it's called
int Tree::getNode() const {
    return node;
}

//getter - returns the vector children - subTrees according to the forum
std::vector<Tree *> Tree::getSubTrees() const {
    return children;
}

//creates a new tree according to the type of the tree
Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == MaxRank)
        return new MaxRankTree(rootLabel);
    else if (session.getTreeType() == Cycle)
        return new CycleTree(rootLabel, session.getCurrCycle());
    else
        return new RootTree(rootLabel);
}

//constructor
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

//clones the tree - uses the copy constructor
Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

/* Starts traversing the tree from the root, picking always the left-most child. Returns
the c'th node in this trip, where c is the cycle in which the tree was created. If the trip is less
than c nodes long, returns the last node in it. */
int CycleTree::traceTree() {
    int treeDepth = 0;
    Tree *leftChild = this;

    //runs until there is something to return
     while(true) {
        //checks if the current cycle of the cycle tree is at tree depth, or if there are no subtrees to the node
        if (leftChild->getSubTrees().empty()) {
            return leftChild->getNode();
        }else if (currCycle == treeDepth){
            return leftChild->getNode();
        }else {
            treeDepth++;
            //sets the current tree to the left most sub tree
            leftChild = leftChild->getSubTrees()[0];
        }
    }
}

//constructor
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

//used by the copy constructor
Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

/*Returns the index of the node in the tree with the highest number of children.
In case of a tie, the node with the smallest depth in the tree would be picked. If there is still a
tie, then the left-most node in that tree would be picked.
*/
int MaxRankTree::traceTree() {
    int maxNodeInd = -1;
    int nodeMaxRank = -1;
    std::queue<Tree *> nodeRankQ;

    nodeRankQ.push(this);

    while (!nodeRankQ.empty()) {
        Tree *currTree = nodeRankQ.front();
        nodeRankQ.pop();

        //we need this vector to add the current tree's children to the queue and to check the its rank
        std::vector<Tree *> currChildren;
        currChildren = currTree->getSubTrees();

        int currRank = currChildren.size(); //to deal with the unsigned integer
        //adds the new children to the queue
        for (int i = 0; i < currRank; i++) {
            nodeRankQ.push(currChildren[i]);
        }
        //if the current rank is higher then the highest node rank we found so far, if so then it replaces it.
        if (currRank > nodeMaxRank) {
            maxNodeInd = currTree->getNode();
            nodeMaxRank = currRank;
        }
    }
    return maxNodeInd;
}

//constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

//runs by the copy constructor
Tree *RootTree::clone() const {
    return new RootTree(*this);
}

//Simply returns the index of the root of the tree.
int RootTree::traceTree() {
    return getNode();
}




