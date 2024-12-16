#include "Dictionary.h"
#include "FileManager.h"
#include "Exceptions.h"
#include <QStringBuilder>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>

Dictionary::Dictionary()
{
    FileManager::loadDictionary(this);
}

Dictionary::~Dictionary()
{
    FileManager::saveDictionary(this);
}

NodeTree* Dictionary::getRoot()
{
	return root;
}

void Dictionary::addNode(const QString& word, NodeTree* current, NodeTree* parent)
{
	if (current == nullptr)
	{
        current = new NodeTree(word);
		if (root == nullptr)
		{
			root = current;
		}
		current->setParent(parent);
		if (parent != nullptr)
		{
            if (word <= parent->getWord())
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
        if (word == current->getWord())
		{
            throw AddExistingException("Слово \"" % word % "\" уже находится в словаре");
		}
        if (word < current->getWord())
		{
            addNode(word, current->getLeft(), current);
		}
		else
		{
            addNode(word, current->getRight(), current);
		}
	}
}

bool Dictionary::searchNode(const QString& word, NodeTree* current)
{
	if (current == nullptr)
    {
        return false;
	}
    if (current->getWord() == word)
	{
        return true;
	}
    if (word < current->getWord())
	{
        return searchNode(word, current->getLeft());
	}
	else
	{
        return searchNode(word, current->getRight());
	}
}

NodeTree* Dictionary::replaceDeleted(NodeTree* deleted)
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

void Dictionary::deleteNode(const QString& word, NodeTree* current)
{
    NodeTree* replaced;
    NodeTree* parent;
    NodeTree* sibling;
    bool bothBlack;

	if (current == nullptr)
	{
        throw DeleteNonExistingException("Слово \"" % word % "\" не найдено в словаре");;
	}

	parent = current->getParent();

    if (word == current->getWord())
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
                std::swap(current->getWord(), replaced->getWord());
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

        std::swap(current->getWord(), replaced->getWord());
        deleteNode(word, replaced);
		return;
	}
    if (word < current->getWord())
	{
        deleteNode(word, current->getLeft());
	}
	else
	{
        deleteNode(word, current->getRight());
	}
}

void Dictionary::fixDelete(NodeTree* deleted)
{
    NodeTree* sibling = deleted->getSibling();
    NodeTree* parent = deleted->getParent();
	bool isChildRed;

	if (deleted == root)
	{
		return;
	}

    isChildRed = (sibling->getLeft() && sibling->getLeft()->getColor() == Color::RED) ||
                 (sibling->getRight() && sibling->getRight()->getColor() == Color::RED);

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

void Dictionary::fixAdd(NodeTree* added)
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
        if ((grandparent->getLeft() == parent && parent->getRight() == added)  ||
            (grandparent->getRight() == parent && parent->getLeft() == added))
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

void Dictionary::leftRotation(NodeTree* node)
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

void Dictionary::rightRotation(NodeTree* node)
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

void Dictionary::deleteTree(NodeTree* current, QXmlStreamWriter& xmlWriter)
{
    if (current == nullptr)
    {
        return;
    }
    deleteTree(current->getLeft(), xmlWriter);
    deleteTree(current->getRight(), xmlWriter);

    xmlWriter.writeTextElement("word", current->getWord());

    delete current;
    current = nullptr;
}

void Dictionary::addNode(const QString& word)
{
    addNode(word, root, nullptr);
}

bool Dictionary::searchNode(const QString& word)
{
    return searchNode(word, root);
}

void Dictionary::deleteNode(const QString& word)
{
    deleteNode(word, root);
}

void Dictionary::setRoot(NodeTree* newRoot)
{
    root = newRoot;
}

void Dictionary::deleteTree(QXmlStreamWriter& xmlWriter)
{
    deleteTree(root, xmlWriter);
}
