#include "RedBlackTree.h"
#include <stdexcept>
#include <string>

// Constructor, creates an empty tree.
// root and numItems already have their default values specified in the header file.
RedBlackTree::RedBlackTree(){
}

// Another constructor that creates a tree with one initial value.
// Here, we reuse Insert() instead of duplicating the code responsible for creating the first node.
RedBlackTree::RedBlackTree(int value){
    Insert(value);
}

// Inserts a value into the tree.
// Right now, we only support inserting the first node,
// but the actual red-black insertion algorithm, including rotations and recoloring, will be implemented later.
void RedBlackTree::Insert(int value){
    // If the tree is empty, the new node becomes its root.
    if (root == nullptr){
        // The root of a red-black tree must always be black.
        root = new RBTNode{
            value,
            COLOR_BLACK,
            nullptr,
            nullptr,
            nullptr
        };
        // We now have exactly one node
        numItems++;

        return;
    }

    // Duplicate values are not allowed according to the assignment!
    if (root->data == value){
        throw std::invalid_argument("Duplicate values are not allowed.");
    }

    // We stop here for now.
    throw std::logic_error(
        "Insert currently supports only the first node."
    );
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
    result += std::to_string(n->data);
    result += (n->color == COLOR_BLACK) ? "B" : "R"; 
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

    return result;
}

// Sources that I used when writing the code:
// https://www.geeksforgeeks.org/cpp/cpp-ternary-or-conditional-operator/#google_vignette