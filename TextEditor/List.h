#pragma once

#include "Node.h"
#include "Iterator.h"

template <typename T>
class List
{
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	unsigned short count;

public:
	void PushFront(T data)
	{
		auto* node = new Node<T>(data);

		if (first)
		{
			node = first = last;
			node->SetNext(nullptr);
		}
		else
		{
			node->SetNext(first);
			first = node;
		}

		node->SetPrev(nullptr);
	}

	void List<T>::PushBack(T data)
	{
		auto node = new Node<T>(data);

		if (first)
		{
			node = first = last;
			node->SetPrev(nullptr);
		}
		else
		{
			node->SetPrev(last);
			last = node;
		}

		node->SetNext(nullptr);
	}
	
	Iterator<Node<T>> begin()
	{
		return Iterator<Node<T>>(first);
	}

	Iterator<Node<T>> end()
	{
		return Iterator<Node<T>>(last);
	}

	Iterator<Node<T>> begin(int offset)
	{
		return Iterator<Node<T>>(first + offset);
	}

	Iterator<Node<T>> end(int offset)
	{
		return Iterator<Node<T>>(last - offset);
	}

	const Iterator<Node<T>> cbegin()
	{
		return Iterator<Node<T>>(first);
	}

	const Iterator<Node<T>> cend()
	{
		return Iterator<Node<T>>(last);
	}

	void DeleteByIndex(unsigned short index)
	{

	}

	Node<T>& operator [] (unsigned short index)
	{
		for each (auto & e : this)
		{

		}
	}
};