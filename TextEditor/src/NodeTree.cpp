#include "NodeTree.h"
#include <iostream>

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

int& NodeTree::getKey()
{
	return key;
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
	std::swap(node1->getKey(), node2->getKey());
}
