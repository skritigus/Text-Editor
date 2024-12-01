#pragma once

#include "NodeTree.h"

class RedBlackTree
{
    NodeTree* root = nullptr;

    void addNode(const int& key, NodeTree* current, NodeTree* parent);
    void searchNode(const int& key, NodeTree* current);
    void deleteNode(const int& key, NodeTree* current);

    NodeTree* replaceDeleted(NodeTree* current);

    void fixAdd(NodeTree* added);
    void fixDelete(NodeTree* deleted);

    void leftRotation(NodeTree* node);
    void rightRotation(NodeTree* node);

    void preorder(NodeTree* node);

public:
    NodeTree* getRoot();

	void addNode(const int& key);
	void searchNode(const int& key);
	void deleteNode(const int& key);

	void preorder();
};
