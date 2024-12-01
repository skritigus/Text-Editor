#include "ReadBlackTree.h"
#include <iostream>

NodeTree* RedBlackTree::getRoot()
{
	return root;
}

void RedBlackTree::addNode(const int& key, NodeTree* current, NodeTree* parent)
{
	if (current == nullptr)
	{
        current = new NodeTree(key);
		if (root == nullptr)
		{
			root = current;
		}
		current->setParent(parent);
		if (parent != nullptr)
		{
			if (key <= parent->getKey())
			{
				parent->setLeft(current);
			}
			else
			{
				parent->setRight(current);
			}
		}
		fixAdd(current);
	}
	else
	{
		if (key == current->getKey())
		{
			return;
		}
		if (key < current->getKey())
		{
			addNode(key, current->getLeft(), current);
		}
		else
		{
			addNode(key, current->getRight(), current);
		}
	}
}

void RedBlackTree::searchNode(const int& key, NodeTree* current)
{
	if (current == nullptr)
	{
		std::cout << "Node " << key << " was NOT found" << std::endl;
		return;
	}
	if (current->getKey() == key)
	{
		std::cout << "Node " << key << " was found" << std::endl;
		return;
	}
	if (key < current->getKey())
	{
		searchNode(key, current->getLeft());
	}
	else
	{
		searchNode(key, current->getRight());
	}
}

NodeTree* RedBlackTree::replaceDeleted(NodeTree* deleted)
{
	if (deleted->getLeft() == nullptr && deleted->getRight() == nullptr)
	{
		return nullptr;
	}

	if (deleted->getLeft() != nullptr && deleted->getRight() != nullptr)
	{
        NodeTree* replaced = deleted->getRight();
		while (replaced->getLeft() != nullptr)
		{
			replaced = replaced->getLeft();
		}
		return replaced;
	}

	if (deleted->getLeft())
	{
		return deleted->getLeft();
	}
	else
	{
		return deleted->getRight();
	}
}

void RedBlackTree::deleteNode(const int& key, NodeTree* current)
{
    NodeTree* replaced;
    NodeTree* parent;
    NodeTree* sibling;
    bool bothBlack;

	if (current == nullptr)
	{
		std::cout << "Node " << key << " was NOT found" << std::endl;
		return;
	}

	parent = current->getParent();

	if (key == current->getKey())
	{
		replaced = replaceDeleted(current);
		bothBlack = current->getColor() == Color::BLACK && (!replaced || replaced->getColor() == Color::BLACK);
		
		if (!replaced)
		{
			if (current == root)
			{
				root = nullptr;
			}
			else
			{
				if (bothBlack)
				{
					fixDelete(current);
				}
				else
				{
					sibling = current->getSibling();
					if (sibling)
					{
						sibling->getColor() = Color::RED;
					}
				}
			}
			delete current;
			current = nullptr;
			return;
		}
		if (current->getLeft() != nullptr ^ current->getRight() != nullptr)
		{
			if (current == root)
			{
				std::swap(current->getKey(), replaced->getKey());
				delete replaced;
				replaced = nullptr;
			}
			else
			{
				delete current;
				current = nullptr;
				if (parent->getLeft() == current)
				{
					parent->setLeft(replaced);
				}
				else
				{
					parent->setRight(replaced);
				}
				replaced->setParent(parent);
				if (bothBlack)
				{
					fixDelete(replaced);
				}
				else
				{
					replaced->setColor(Color::BLACK);
				}
			}
			return;
		}

		std::swap(current->getKey(), replaced->getKey());
		deleteNode(key, replaced);
		return;
	}
	if (key < current->getKey())
	{
		deleteNode(key, current->getLeft());
	}
	else
	{
		deleteNode(key, current->getRight());
	}
}

void RedBlackTree::fixDelete(NodeTree* deleted)
{
    NodeTree* sibling = deleted->getSibling();
    NodeTree* parent = deleted->getParent();
	bool isChildRed;

	if (deleted == root)
	{
		return;
	}
	
	if (!sibling)
	{
		fixDelete(parent);
	}

	isChildRed = sibling->getLeft() && sibling->getLeft()->getColor() == Color::RED ||
				 sibling->getRight() && sibling->getRight()->getColor() == Color::RED;

	if (sibling->getColor() == Color::BLACK)
	{
		if (!isChildRed)
		{
			sibling->setColor(Color::RED);
			if (parent->getColor() == Color::RED)
			{
				parent->setColor(Color::BLACK);
			}
			else
			{
				fixDelete(parent);
			}
			return;
		}

		if (parent->getLeft() == sibling)
		{
			if (sibling->getRight() && !sibling->getLeft())
			{
                NodeTree* child = sibling->getRight();
				std::swap(sibling->getColor(), child->getColor());
				leftRotation(sibling);
				std::swap(sibling, child);
			}
			std::swap(sibling->getColor(), parent->getColor());
			sibling->getLeft()->setColor(Color::BLACK);
			parent->setColor(Color::BLACK);
			rightRotation(parent);
		}
		else
		{
			if (sibling->getLeft() && !sibling->getRight())
			{
                NodeTree* child = sibling->getLeft();
				std::swap(sibling->getColor(), sibling->getLeft()->getColor());
				rightRotation(sibling);
				std::swap(sibling, child);
			}
			std::swap(sibling->getColor(), parent->getColor());
			sibling->getRight()->setColor(Color::BLACK);
			parent->setColor(Color::BLACK);
			leftRotation(parent);
		}
		return;
	}
	else
	{
		if (parent->getLeft() == sibling)
		{
			rightRotation(parent);
			sibling->setColor(Color::BLACK);
			parent->setColor(Color::RED);
		}
		else
		{
			leftRotation(parent);
			sibling->setColor(Color::BLACK);
			parent->setColor(Color::RED);
		}
		fixDelete(deleted);
	}
}

void RedBlackTree::fixAdd(NodeTree* added)
{
	if (added == root)
	{
		added->setColor(Color::BLACK);
		return;
	}

    NodeTree* parent = added->getParent();
	if (parent->getColor() == Color::BLACK)
	{
		return;
	}

    NodeTree* grandparent = parent->getParent();
    NodeTree* uncle;

	if (grandparent->getLeft() == parent)
	{
		uncle = grandparent->getRight();
	}
	else
	{
		uncle = grandparent->getLeft();
	}

	if (uncle != nullptr && uncle->getColor() == Color::RED)
	{
		parent->setColor(Color::BLACK);
		uncle->setColor(Color::BLACK);
		grandparent->setColor(Color::RED);
		fixAdd(grandparent);
	}
	else
	{
        if (grandparent->getLeft() == parent && parent->getRight() == added  ||
			grandparent->getRight() == parent && parent->getLeft() == added)
		{
			if (parent->getRight() == added)
			{
				leftRotation(parent);
			}
			else
			{
				rightRotation(parent);
			}
			std::swap(added, parent);
		}

		parent->setColor(Color::BLACK);
		grandparent->setColor(Color::RED);
		if (grandparent->getLeft() == parent)
		{
			rightRotation(grandparent);
		}
		else
		{
			leftRotation(grandparent);
		}
	}
}

void RedBlackTree::leftRotation(NodeTree* node)
{
    NodeTree* rtree = node->getRight();
    NodeTree* temp = rtree->getLeft();
    NodeTree* parent = node->getParent();

	if (temp != nullptr)
	{
		temp->setParent(node);
	}
	rtree->setParent(parent);
	if (parent == nullptr)
	{
		root = rtree;
	}
	else
	{
		if (parent->getLeft() == node)
		{
			parent->setLeft(rtree);
		}
		else
		{
			parent->setRight(rtree);
		}
	}
	node->setParent(rtree);
	rtree->setLeft(node);
	node->setRight(temp);
}

void RedBlackTree::rightRotation(NodeTree* node)
{
    NodeTree* ltree = node->getLeft();
    NodeTree* temp = ltree->getRight();
    NodeTree* parent = node->getParent();

	ltree->setParent(parent);
	if (parent == nullptr)
	{
		root = ltree;
	}
	else
	{
		if (parent->getLeft() == node)
		{
			parent->setLeft(ltree);
		}
		else
		{
			parent->setRight(ltree);
		}
	}

	node->setParent(ltree);
	ltree->setRight(node);

	if (temp != nullptr)
	{
		temp->setParent(node);
	}
	node->setLeft(temp);
}

void RedBlackTree::preorder(NodeTree* node)
{
	if (node != nullptr)
	{
		std::cout << node->getKey() << "(" << (int)node->getColor() << ") " << std::endl;
		preorder(node->getLeft());
		preorder(node->getRight());
	}
}

void RedBlackTree::addNode(const int& key)
{
	this->addNode(key, root, nullptr);
}

void RedBlackTree::searchNode(const int& key)
{
	this->searchNode(key, root);
}

void RedBlackTree::deleteNode(const int& key)
{
	this->deleteNode(key, root);
}

void RedBlackTree::preorder()
{
	this->preorder(root);
}
