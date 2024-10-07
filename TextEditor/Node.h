#pragma once

#include "FontStyle.h"

template <typename T>
class Node
{
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;

public:
	explicit Node(const T& data)
	{
		this->data = data;
	}

	Node<T>* GetNext()
	{
		return next;
	}

	Node<T>* GetPrev()
	{
		return prev;
	}

	T& GetData()
	{
		return data;
	}

	void SetNext(Node<T>* node)
	{
		next = node;
	}

	void SetPrev(Node<T>* node)
	{
		prev = node;
	}

	void SetData(T newData)
	{
		data = newData;
	}

	bool operator==(Node<T>& node)
	{
		return data == node.GetData();
	}

	auto operator<=>(Node<T>& other)
	{
		return data <=> other.data;
	}
};