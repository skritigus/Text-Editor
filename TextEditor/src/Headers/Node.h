#pragma once

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

	Node<T>* getNext()
	{
		return next;
	}

	Node<T>* getPrev()
	{
		return prev;
	}

	T& getData()
	{
		return data;
	}

	void setNext(Node<T>* node)
	{
		next = node;
	}

	void setPrev(Node<T>* node)
	{
		prev = node;
	}

	void setData(T newData)
	{
		data = newData;
	}

	bool operator==(Node<T>& node)
	{
		return data == node.getData();
	}

	auto operator<=>(Node<T>& node)
	{
		return data <=> node.getData();
	}
};