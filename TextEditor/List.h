#pragma once

#include "Node.h"
#include "ListIterator.h"

template <typename T>
class List
{
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	int count = 0;

	Node<T>* partition(Node<T>* low, Node<T>* high)
	{
		ListIterator<T> it1 = begin(low);
		ListIterator<T> it2(it1);
		ListIterator<T> fin = end(high);

		for (; it1 != fin; ++it1)
		{
			if (*it1 <= *fin)
			{
				SwapNodes(*it1, *it2);
				++it2;
			}
		}
		SwapNodes(*it2, *fin);

		return it2.GetPtr();
	}

	void quickSort(Node<T>* low, Node<T>* high)
	{
		if (low && high && low != high)
		{
			Node<T>* pi = partition(low, high);

			quickSort(low, pi->GetPrev());
			quickSort(pi->GetNext(), high);
		}
	}

public:
	int GetCount() const
	{
		return count;
	}

	Node<T>* GetFirst()
	{
		return first;
	}

	Node<T>* GetLast()
	{
		return last;
	}

	void PushFront(T& data)
	{
		auto* node = new Node<T>(data);

		++count;

		if (!first)
		{
			first = last = node;
			return;
		}
		node->SetNext(first);
		node->GetNext()->SetPrev(node);
		first = node;
	}

	void PushBack(T& data)
	{
		auto* node = new Node<T>(data);

		++count;

		if (!first)
		{
			first = last = node;
			return;
		}
		node->SetPrev(last);
		node->GetPrev()->SetNext(node);
		last = node;
	}

	ListIterator<T> begin(Node<T>* start)
	{
		return ListIterator<T>(start);
	}

	ListIterator<T> end(Node<T>* fin)
	{
		return ListIterator<T>(fin);
	}

	const ListIterator<T>& cbegin() const
	{
		return ListIterator<T>(first);
	}

	const ListIterator<T>& cend() const
	{
		return ListIterator<T>(nullptr); 
	}

	Node<T>& operator[](int index)
	{
		Node<T>* node;
		if (index < count >> 1)
		{
			node = first;
			for (int i = 0; i < index; ++i)
			{
				node = node->GetNext();
			}
		}
		else
		{
			node = last;
			for (int i = count - 1; i > index; --i)
			{
				node = node->GetPrev();
			}
		}

		return *node;
	}

	void PopBack()
	{
		auto* temp = last;

		last = temp->GetPrev();
		if (temp->GetPrev())
		{
			temp->GetPrev()->SetNext(nullptr);
		}
		delete temp;
		temp = nullptr;

		--count;
	}

	void DeleteByIndex(int index)
	{
		auto* temp = &((*this)[index]);

		if (temp->GetNext())
		{
			temp->GetNext()->SetPrev(temp->GetPrev());
		}
		else
		{
			last = temp->GetPrev();
		}
		if (temp->GetPrev())
		{
			temp->GetPrev()->SetNext(temp->GetNext());
		}
		else
		{
			first = temp->GetNext();
		}
		delete temp;
		temp = nullptr;

		--count;
	}

	inline void SwapNodes(Node<T>& node1, Node<T>& node2) const
	{
		std::swap(node1.GetData(), node2.GetData());
	}

	void QuickSort()
	{
		quickSort(first, last);
	}
};
