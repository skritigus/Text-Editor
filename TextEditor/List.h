#pragma once

#include "Node.h"
#include "ListIterator.h"

template <typename T>
class List
{
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	unsigned short count = 0;

	int Partition(int low, int high)
	{

		int i = low - 1;

		for (int j = low; j < high; ++j)
		{
			if ((*this)[j] <= (*this)[high])
			{
				++i;
				SwapNodes((*this)[i], (*this)[j]);
			}
		}

		SwapNodes((*this)[i + 1], (*this)[high]);

		return i + 1;
	}

	void QuickSort(int low, int high)
	{
		if (low < high)
		{
			int pi = Partition(low, high);

			QuickSort(low, pi - 1);
			QuickSort(pi + 1, high);
		}
	}

public:
	unsigned short GetCount() const
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
	
	ListIterator<T> begin()
	{
		return ListIterator<T>(first);
	}

	ListIterator<T> end()
	{
		return ListIterator<T>(last);
	}

	ReverseListIterator<T> rbegin()
	{
		return ReverseListIterator<T>(last);
	}

	ReverseListIterator<T> rend()
	{
		return ReverseListIterator<T>(nullptr);
	}

	const ListIterator<T>& cbegin() const
	{
		return ListIterator<T>(first);
	}

	const ListIterator<T>& cend() const
	{
		return ListIterator<T>(nullptr); 
	}

	Node<T>& operator[](unsigned short index)
	{
		if (index >= count)
		{
			throw std::exception(std::string("Invalid index: " + std::to_string(index)).c_str());
		}

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

	void DeleteByIndex(unsigned short index)
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
		QuickSort(0, count - 1);
	}
};