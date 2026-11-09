#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <string>

// We represent node colors using integers, because
// this makes it easier to check and change colors later
#define COLOR_RED 0
#define COLOR_BLACK 1

// Each node stores one integer and pointers to its children and its parent.
// Parent pointer will be useful when we need to implement rotations and red-black tree balancing.
struct RBTNode{
    int data;
    int color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
};

class RedBlackTree{
public:
    RedBlackTree();

    // Creates a tree containing one initial value.
    RedBlackTree(int value);

        // Copy constructor.
    RedBlackTree(const RedBlackTree& other);

    // Checks if a value exists in the tree.
    bool Contains(int value) const;

    // Returns the smallest value.
    int GetMin() const;

    // Returns the largest value.
    int GetMax() const;

    // Returns the number of nodes.
    unsigned long long int Size() const;

    // Inserts a value into the tree.
    // Right now, only insertion into an empty tree is implemented.
    void Insert(int value);
    // For tests that I made.
    void PrivateTests();

    // Returns the values using three different traversal orders.
    // These wrappers call private recursive functions.
    std::string ToInfixString() const{
        return ToInfixString(root);
    }

    std::string ToPrefixString() const{
        return ToPrefixString(root);
    }

    std::string ToPostfixString() const{
        return ToPostfixString(root);
    }

private:
    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;

    // Functions for balancing the tree.
    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);
    void FixInsert(RBTNode* node);

    // Helper functions.
    RBTNode* FindNode(int value) const;
    RBTNode* MinimumNode(RBTNode* node) const;
    RBTNode* MaximumNode(RBTNode* node) const;
    RBTNode* CopySubtree(RBTNode* node, RBTNode* parent);

    // Recursive traversal functions.
    std::string ToInfixString(RBTNode* node) const;
    std::string ToPrefixString(RBTNode* node) const;
    std::string ToPostfixString(RBTNode* node) const;
};

#endif