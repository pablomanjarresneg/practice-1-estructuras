#include "../include/balancedtree.h"
#include <algorithm>

using namespace std;
//- node = current tree node (a pointer to one AVLNode)
//- node->left = pointer to node’s left child
//- node->right = pointer to node’s right child

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() { //we define the destructor method
    destroy(root);
}

void AVLTree::destroy(AVLNode* node) { //destroys recursively all the subtrees and at the end deletes the root node
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVLTree::height(AVLNode* node) const { //if there is a node it returns the height of it, if not it returns 0
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(AVLNode* node) const { //if there is a node, it returns the difference between the height of the left and right subtree, if not (null node) it returns 0
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left; // x is the left child of y
    AVLNode* T2 = x->right; //T2 is the subtree that will be moved

    x->right = y; // y becomes the right child of x
    y->left = T2; // T2 becomes the left child of y

    y->height = 1 + max(height(y->left), height(y->right)); // update y first
    x->height = 1 + max(height(x->left), height(x->right)); // then update x

    return x; //new root of this subtree
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right; // x is the right child of y
    AVLNode* T2 = y->left; // T2 is the subtree that will be moved

    y->left = x; // x becomes the left child y
    x->right = T2; // T2 becomes the right child of x

    x->height = 1 + max(height(x->left), height(x->right)); // x first
    y->height = 1 + max(height(y->left), height(y->right)); // then y

    return y;
}

AVLNode* AVLTree::insertNode(AVLNode* node, const string& key) {
    if (!node) return new AVLNode(key);

    if (key < node->key) //if the key to insert is less than the current node's key, we go to the left subtree
        //node->left implies pointer to its left child node
        node->left = insertNode(node->left, key);
    else if (key > node->key) // otherwise we go the right subtree
        node->right = insertNode(node->right, key);
    else
        return node; // duplicate keys ignored

    node->height = 1 + max(height(node->left), height(node->right)); //calculate the height

    int balance = balanceFactor(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rotateRight(node); //too left heavy so rotate to right

    // Right Right
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node); // too right heavy

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) { // comparing using the node key and the key of the right subtree
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(const string& key) { //key =value of the node
    root = insertNode(root, key);
}

void AVLTree::inorderTraversal(AVLNode* node, vector<string>& result) const {
    if (!node) return;
    inorderTraversal(node->left, result); //visits constantly the left node and stores the key on result
    result.push_back(node->key);
    inorderTraversal(node->right, result);//visits constantly the left node and stores the key on result
}

void AVLTree::inorder(vector<string>& result) const {
    inorderTraversal(root, result);
}
