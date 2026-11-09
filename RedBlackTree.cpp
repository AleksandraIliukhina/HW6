#include "RedBlackTree.h"
#include <stdexcept>
#include <string>
#include <cassert>

// Constructor, creates an empty tree.
RedBlackTree::RedBlackTree(){
}

// Another constructor that creates a tree with one initial value.
// Here, we reuse Insert() instead of duplicating the code responsible for creating the first node.
RedBlackTree::RedBlackTree(int value){
    Insert(value);
}

// Inserts a value into the tree.
void RedBlackTree::Insert(int value){
    RBTNode* parent = nullptr;
    RBTNode* current = root;
    // If the tree is empty, the new node becomes its root.
    while (current != nullptr){
        parent = current;
        if (current->data == value){
            // Duplicate values are not allowed according to the assignment!
            throw std::invalid_argument("Duplicate values are not allowed.");
        }

        if (value < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    RBTNode* newNode = new RBTNode{value, COLOR_RED, nullptr, nullptr, parent};
    if (parent == nullptr){
        root = newNode;
    }else if(value < parent->data){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
    numItems++;
    FixInsert(newNode);
        return;
    }

// Left rotation.
void RedBlackTree::RotateLeft(RBTNode* node){
    RBTNode* pivot = node->right;
    node->right = pivot->left;

    if(pivot->left != nullptr){
        pivot->left->parent = node;
    }

    pivot->parent = node->parent;
    if(node->parent == nullptr){
        root = pivot;
    }
    else if(node == node->parent->left){
        node->parent->left = pivot;
    }else{
        node->parent->right = pivot;
    }
    pivot->left = node;
    node->parent = pivot;
}

// Right rotation.
void RedBlackTree::RotateRight(RBTNode* node){
    RBTNode* pivot = node->left;
    node->left = pivot->right;

    if(pivot->right != nullptr){
        pivot->right->parent = node;
    }
    pivot->parent = node->parent;

    if(node->parent == nullptr){
        root = pivot;
    }else if(node == node->parent->right){
        node->parent->right = pivot;
    }else{
        node->parent->left = pivot;
    }

    pivot->right = node;
    node->parent = pivot;
}

// Restores red-black properties after insertion
void RedBlackTree::FixInsert(RBTNode* node){
    while (node != root && node->parent != nullptr && node->parent->color == COLOR_RED){
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;
        if(parent == grandparent->left){
            RBTNode* uncle = grandparent->right;
            if(uncle != nullptr && uncle->color == COLOR_RED){
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                node = grandparent;
            }else{
                if(node == parent->right){
                    node = parent;
                    RotateLeft(node);

                    parent = node->parent;
                    grandparent = parent->parent;
                }
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                RotateRight(grandparent);
            }
        }else{
            RBTNode* uncle = grandparent->left;
            if(uncle != nullptr && uncle->color == COLOR_RED){
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            }else{
                    if (node == parent->left){
                    node = parent;
                    RotateRight(node);

                    parent = node->parent;
                    grandparent = parent->parent;
                }
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                RotateLeft(grandparent);
            }
        }
    }
    root->color = COLOR_BLACK;
}

// Searches for a node with the given value
RBTNode* RedBlackTree::FindNode(int value) const{
    RBTNode* current = root;
    while (current != nullptr){
        if (current->data == value){
            return current;
        }
        if (value < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    return nullptr;
}

// Finds the smallest node.
RBTNode* RedBlackTree::MinimumNode(RBTNode* node) const{
    if(node == nullptr){
        return nullptr;
    }
    while(node->left != nullptr){
        node = node->left;
    }

    return node;
}

// Finds the largest node
RBTNode* RedBlackTree::MaximumNode(RBTNode* node) const{
    if(node == nullptr){
        return nullptr;
    }

    while(node->right != nullptr){
        node = node->right;
    }

    return node;
}

// inorder:  Left -> Root -> Right
// and recursion allows us to process every subtree using the same logic
std::string RedBlackTree::ToInfixString(RBTNode* n) const{
    // Base case: an empty subtree contributes nothing
    if (n == nullptr){
        return "";
    }
    // Visit left subtree first
    std::string result = ToInfixString(n->left);
    // Add the current node. The space and color letter are required by the tests
    result += " ";
    // the "?" symbol is a "ternary operator" that is checking the condition. if true, then "B", if false, then "R"
    result += (n->color == COLOR_BLACK) ? "B" : "R";
    result += std::to_string(n->data);
    result += " ";
    // Visit right subtree
    result += ToInfixString(n->right);

    return result;
}

// preorder: Root -> Left -> Right
std::string RedBlackTree::ToPrefixString(RBTNode* n) const{
    if (n == nullptr){
        return "";
    }

    std::string result = " ";
    result += (n->color == COLOR_BLACK) ? "B" : "R";
    result += std::to_string(n->data);
    result += " ";
    result += ToPrefixString(n->left);
    result += ToPrefixString(n->right);

    return result;
}

// postorder: Left -> Right -> Root
std::string RedBlackTree::ToPostfixString(RBTNode* n) const{
    if (n == nullptr){
        return "";
    }
    std::string result = ToPostfixString(n->left);
    result += ToPostfixString(n->right);
    result += " ";
    result += (n->color == COLOR_BLACK) ? "B" : "R";
    result += std::to_string(n->data);
    result += " ";

    return result;}
// Tests for some private helper functions. These tests use stack-allocated nodes, so they do not create memory leaks.
void RedBlackTree::PrivateTests(){
    // test 1: FindNode, MinimumNode and MaximumNode
    RedBlackTree searchTree;

    RBTNode leftNode ={
        10, COLOR_RED, nullptr, nullptr, nullptr
    };

    RBTNode rightNode ={
        30, COLOR_RED, nullptr, nullptr, nullptr
    };

    RBTNode centerNode ={
        20, COLOR_BLACK, &leftNode, &rightNode, nullptr
    };

    leftNode.parent = &centerNode;
    rightNode.parent = &centerNode;

    searchTree.root = &centerNode;
    searchTree.numItems = 3;

    assert(searchTree.FindNode(20) == &centerNode);
    assert(searchTree.FindNode(10) == &leftNode);
    assert(searchTree.FindNode(100) == nullptr);
    assert(searchTree.MinimumNode(&centerNode) == &leftNode);
    assert(searchTree.MaximumNode(&centerNode) == &rightNode);

    // Test 2: RotateLeft and RotateRight
    RedBlackTree rotationTree;

    RBTNode left ={
        10, COLOR_RED, nullptr, nullptr, nullptr
    };

    RBTNode middle ={
        20, COLOR_BLACK, &left, nullptr, nullptr
    };

    RBTNode right ={
        30, COLOR_RED, nullptr, nullptr, &middle
    };

    middle.parent = nullptr;
    middle.right = &right;
    left.parent = &middle;

    rotationTree.root = &middle;
    rotationTree.numItems = 3;

    rotationTree.RotateLeft(&middle);
    assert(rotationTree.root == &right);
    assert(right.left == &middle);
    assert(middle.parent == &right);
    rotationTree.RotateRight(&right);
    assert(rotationTree.root == &middle);
    assert(middle.right == &right);
    assert(right.parent == &middle);

    // Test 3: FixInsert
    // A red parent and red child in a left-left configuration
    // should be fixed by recoloring and a right rotation.
    RedBlackTree fixTree;

    RBTNode child ={
        5, COLOR_RED, nullptr, nullptr, nullptr
    };

    RBTNode parent ={
        10, COLOR_RED, &child, nullptr, nullptr
    };

    RBTNode grandparent ={
        20, COLOR_BLACK, &parent, nullptr, nullptr
    };

    parent.parent = &grandparent;
    child.parent = &parent;

    fixTree.root = &grandparent;
    fixTree.numItems = 3;

    fixTree.FixInsert(&child);
    assert(fixTree.root == &parent);
    assert(parent.color == COLOR_BLACK);
    assert(grandparent.color == COLOR_RED);
    assert(parent.right == &grandparent);
}

// Sources that I used when writing the code:
// https://www.tutorialspoint.com/data_structures_algorithms/red_black_trees.htm 
// https://www.geeksforgeeks.org/cpp/cpp-ternary-or-conditional-operator/#google_vignette