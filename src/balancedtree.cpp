#include "../include/balancedtree.h"
#include <algorithm>

using namespace std;

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroy(root);
}

void AVLTree::destroy(AVLNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

AVLNode* AVLTree::insertNode(AVLNode* node, const string& key) {
    if (!node) return new AVLNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // duplicate keys ignored

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(const string& key) {
    root = insertNode(root, key);
}

void AVLTree::inorderTraversal(AVLNode* node, vector<string>& result) const {
    if (!node) return;
    inorderTraversal(node->left, result);
    result.push_back(node->key);
    inorderTraversal(node->right, result);
}

void AVLTree::inorder(vector<string>& result) const {
    inorderTraversal(root, result);
}
