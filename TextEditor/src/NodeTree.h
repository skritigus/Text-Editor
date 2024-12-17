#ifndef NODETREE_H
#define NODETREE_H

#include <QString>

enum class Color { RED, BLACK };

class NodeTree
{
    QString word;
	Color color = Color::RED;
    NodeTree* left = nullptr;
    NodeTree* right = nullptr;
    NodeTree* parent = nullptr;

public:
    explicit NodeTree(const QString& word) : word(word) {};
    ~NodeTree();

    NodeTree* getLeft();
    NodeTree* getRight();
    NodeTree* getParent();
    NodeTree* getSibling();
	Color& getColor();
    QString& getWord();

	void setColor(const Color& newColor);
    void setLeft(NodeTree* node);
    void setRight(NodeTree* node);
    void setParent(NodeTree* node);

    static void swapNodes(NodeTree* node1, NodeTree* node2);
};

#endif
