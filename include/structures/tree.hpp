#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct TreeNode
{
    std::string value;
    unsigned count;
    TreeNode* left, * right;
};

void add(const std::string& val, TreeNode*& root);
void clear(TreeNode*& root);

TreeNode* find(const std::string& val, TreeNode* root);

void print(const TreeNode* root);

TreeNode* find_to_remove(const std::string& val, TreeNode* root, TreeNode*& parent, char& dir);

void remove(const std::string& val, TreeNode*& root);