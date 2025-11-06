#include <iostream>
#include <fstream>
#include <string>
#include "structures/tree.hpp"

using namespace std;


void add(const string& val, TreeNode*& root)
{
    if (root == nullptr)
    {
        root = new TreeNode;
        root->value = val;
        root->count = 1;
        root->left = root->right = nullptr;
        return;
    }
    if (val == root->value)
    {
        ++root->count;
        return;
    }
    if (val < root->value)
        if (root->left != nullptr)
            add(val, root->left);
        else
        {
            root->left = new TreeNode;
            root->left->value = val;
            root->left->count = 1;
            root->left->left = root->left->right = nullptr;
            return;
        }
    else
        if (root->right != nullptr)
            add(val, root->right);
        else
        {
            root->right = new TreeNode;
            root->right->value = val;
            root->right->count = 1;
            root->right->left = root->right->right = nullptr;
            return;
        }
}

void clear(TreeNode*& root)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
        clear(root->left);
    if (root->right != nullptr)
        clear(root->right);
    delete root;
    root = nullptr;
    return;
}

TreeNode* find(const string& val, TreeNode* root)
{
    if (root == nullptr)
        return nullptr;
    if (val == root->value)
        return root;
    if (val < root->value && root->left != nullptr)
        return find(val, root->left);
    if (val > root->value && root->right != nullptr)
        return find(val, root->right);
    return nullptr;
}

void print(const TreeNode* root)
{
    if (root == nullptr)
    {
        cout << "Tree is empty!";
        return;
    }
    if (root->left != nullptr)
        print(root->left);
    for (unsigned i = 0; i < root->count; ++i)
        cout << root->value << ' ';
    if (root->right != nullptr)
        print(root->right);
    return;
}

TreeNode* find_to_remove(const string& val, TreeNode* root, TreeNode*& parent, char& dir)
{
    if (root == nullptr)
    {
        parent = nullptr;
        return nullptr;
    }
    if (val == root->value)
        return root;
    if (val < root->value && root->left != nullptr)
    {
        dir = 'L';
        parent = root;
        return find(val, root->left);
    }
    if (val > root->value && root->right != nullptr)
    {
        dir = 'R';
        parent = root;
        return find(val, root->right);
    }
    parent = nullptr;
    return nullptr;
}

void remove(const string& val, TreeNode*& root)
{
    if (root == nullptr)
        return;
    TreeNode* parent = nullptr, * rem;
    char dir;
    rem = find_to_remove(val, root, parent, dir);
    
    if (rem == nullptr)
        return;
        
    if (rem->left == nullptr && rem->right == nullptr)
    {
        delete rem;
        if (rem == root)
            root = nullptr;
        if (dir == 'L')
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }
    else if (rem->left != nullptr && rem->right == nullptr)
    {
        if (rem == root)
        {
            root = root->left;
            delete rem;
            return;
        }
        if (dir == 'L')
            parent->left = rem->left;
        else
            parent->right = rem->left;
        delete rem;
    }
    else if (rem->left == nullptr && rem->right != nullptr)
    {
        if (rem == root)
        {
            root = root->right;
            delete rem;
            return;
        }
        if (dir == 'L')
            parent->left = rem->right;
        else
            parent->right = rem->right;
        delete rem;
    }
    else
    {
        TreeNode* max;
        parent = rem;
        max = rem->left;
        while (max->right != nullptr)
        {
            parent = max;
            max = max->right;
        }
        rem->value = max->value;
        rem->count = max->count;
        parent->right = max->left;
        delete max;
    }
}