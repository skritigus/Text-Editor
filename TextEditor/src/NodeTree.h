#pragma once

enum class Color { RED, BLACK };

class NodeTree
{
	int key;
	Color color = Color::RED;
    NodeTree* left = nullptr;
    NodeTree* right = nullptr;
    NodeTree* parent = nullptr;

public:
    NodeTree(const int& key) : key(key) {};
    ~NodeTree();

    NodeTree* getLeft();
    NodeTree* getRight();
    NodeTree* getParent();
    NodeTree* getSibling();
	Color& getColor();
	int& getKey();

	void setColor(const Color& newColor);
    void setLeft(NodeTree* node);
    void setRight(NodeTree* node);
    void setParent(NodeTree* node);

    static void swapNodes(NodeTree* node1, NodeTree* node2);
};
