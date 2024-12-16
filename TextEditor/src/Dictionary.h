#pragma once
#include "NodeTree.h"
#include <QXmlStreamWriter>
#include <QJsonArray>
#include <QDomDocument>

class Dictionary
{
    NodeTree* root = nullptr;

    void addNode(const QString& word, NodeTree* current, NodeTree* parent);
    bool searchNode(const QString& word, NodeTree* current);
    void deleteNode(const QString& word, NodeTree* current);

    void deleteTree(NodeTree* current, QXmlStreamWriter& xmlWriter);

    NodeTree* replaceDeleted(NodeTree* current);

    void fixAdd(NodeTree* added);
    void fixDelete(NodeTree* deleted);

    void leftRotation(NodeTree* node);
    void rightRotation(NodeTree* node);

public:
    Dictionary();
    ~Dictionary();

    NodeTree* getRoot();

    void setRoot(NodeTree* root);

    void addNode(const QString& word);
    bool searchNode(const QString& word);
    void deleteNode(const QString& word);

    void deleteTree(QXmlStreamWriter& xmlWriter);
};
