#include "NodeTree.h"

NodeTree::~NodeTree()
{
	left = nullptr;
	right = nullptr;
	if (parent)
	{
		if (parent->getLeft() == this)
		{
			parent->setLeft(nullptr);
		}
		else
		{
			parent->setRight(nullptr);
		}
	}
	parent = nullptr;
}

NodeTree* NodeTree::getLeft()
{
	return left;
}

NodeTree* NodeTree::getRight()
{
	return right;
}

NodeTree* NodeTree::getParent()
{
	return parent;
}

NodeTree* NodeTree::getSibling()
{
	if (!parent)
	{
		return nullptr;
	}

	if (parent->getLeft() == this)
	{
		return parent->getRight();
	}
	else
	{
		return parent->getLeft();
	}
}

QString& NodeTree::getWord()
{
    return word;
}

Color& NodeTree::getColor()
{
	return color;
}

void NodeTree::setColor(const Color& newColor)
{
	color = newColor;
}

void NodeTree::setLeft(NodeTree* node)
{
	left = node;
}

void NodeTree::setRight(NodeTree* node)
{
	right = node;
}

void NodeTree::setParent(NodeTree* node)
{
	parent = node;
}

void NodeTree::swapNodes(NodeTree* node1, NodeTree* node2)
{
    std::swap(node1->getWord(), node2->getWord());
}
