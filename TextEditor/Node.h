#pragma once

#include "FontStyle.h"

template <typename T>
class Node
{
	T data;
	Node* next;
	Node* prev;

public:
	Node<T>::Node(T data)
	{
		this->data = data;
	}

	Node<T>* Node<T>::GetNext()
	{
		return next;
	}

	Node<T>* Node<T>::GetPrev()
	{
		return prev;
	}

	T Node<T>::GetData()
	{
		return data;
	}

	void Node<T>::SetNext(Node<T>* next)
	{
		this->next = next;
	}

	void Node<T>::SetPrev(Node<T>* prev)
	{
		this->prev = prev;
	}

	void Node<T>::SetData(T data)
	{
		this->data = data;
	}
};