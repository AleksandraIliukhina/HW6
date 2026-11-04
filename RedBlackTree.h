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

    // Inserts a value into the tree.
    // Right now, only insertion into an empty tree is implemented.
    void Insert(int value);

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
    // Recursive traversal helpers.
    // A nullptr node represents an empty subtree.
    std::string ToInfixString(RBTNode* n) const;
    std::string ToPrefixString(RBTNode* n) const;
    std::string ToPostfixString(RBTNode* n) const;

    // Required instance variables from the assignment.
    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;
};

#endif