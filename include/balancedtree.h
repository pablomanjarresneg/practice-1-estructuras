#ifndef PRACTICE_1_ESTRUCTURAS_BALANCEDTREE_H
#define PRACTICE_1_ESTRUCTURAS_BALANCEDTREE_H

#include <string>
#include <vector>

struct AVLNode {
    std::string key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const std::string& k)
        : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const std::string& key);
    void inorder(std::vector<std::string>& result) const;

private:
    AVLNode* root;

    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, const std::string& key);
    void inorderTraversal(AVLNode* node, std::vector<std::string>& result) const;
    void destroy(AVLNode* node);
};

#endif
