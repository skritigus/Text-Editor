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
				swapNodes(*it1, *it2);
				++it2;
			}
		}
		swapNodes(*it2, *fin);

		return it2.getPtr();
	}

    void quickSort(Node<T>* low, Node<T>* high)
	{
		if (low && high && low != high)
		{
            Node<T>* pi = partition(low, high);

			quickSort(low, pi->getPrev());
			quickSort(pi, high);
		}
	}

public:
	List() = default;

    List(const List<T>& other) : first(other.first), last(other.last), count(other.count) {}

	List(List<T>&& other) noexcept : first(other.first), last(other.last), count(other.count)
	{
		other.first = nullptr;
		other.last = nullptr;
	}

	~List()
    {
        clear();
	}

	int getCount() const
	{
		return count;
	}

    Node<T>* getFirst()
	{
		return first;
	}

    Node<T>* getLast()
	{
		return last;
	}

    void pushFront(T& data)
    {
        auto* node = new Node<T>(data);

        ++count;

        if (!first)
        {
            first = last = node;
            return;
        }
        node->setNext(first);
        node->getNext()->setPrev(node);
        first = node;
    }

    void pushBack(const T& data)
	{
        auto* node = new Node<T>(data);

		++count;

		if (!first)
		{
			first = last = node;
			return;
		}
		node->setPrev(last);
		node->getPrev()->setNext(node);
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

	ListIterator<T> cbegin() const
	{
		return ListIterator<T>(first);
	}

	ListIterator<T> cend() const
	{
		return ListIterator<T>(nullptr); 
	}

    Node<T>& operator[](const int& index)
	{
        Node<T>* node;

		if (index < count >> 1)
		{
			node = first;
			for (int i = 0; i < index; ++i)
			{
                node = node->getNext();
			}
		}
		else
		{
			node = last;
			for (int i = count - 1; i > index; --i)
			{
                node = node->getPrev();
            }
		}

        return *node;
	}

    Node<T>& operator[](const int& index) const
    {
        Node<T>* node;

        if (index < count >> 1)
        {
            node = first;
            for (int i = 0; i < index; ++i)
            {
                node = node->getNext();
            }
        }
        else
        {
            node = last;
            for (int i = count - 1; i > index; --i)
            {
                node = node->getPrev();
            }
        }

        return *node;
    }

    void popFront()
    {
        auto* temp = first;

        if (first == last)
        {
            first = last = nullptr;
        }
        else
        {
            first = first->getNext();
            first->setPrev(nullptr);
        }
        delete temp;

        --count;
    }

	void popBack()
	{
        auto* temp = last;

		if (first == last)
		{
			first = last = nullptr;
		}
		else
		{
			last = last->getPrev();
			last->setNext(nullptr);
		}
        delete temp;

		--count;
	}

    void clear()
    {
        for (ListIterator<T> it1 = cbegin(), it2(it1), end = cend(); it1 != end;)
        {
            ++it1;
            delete it2.getPtr();
            it2 = it1;
        }
        first = nullptr;
        last = nullptr;
        count = 0;
    }

	void deleteByIndex(int index)
    {
        deleteByNode(&((*this)[index]));
	}

    void deleteByNode(Node<T>* node)
    {
        Node<T>* temp = node;

        if (temp->getNext())
        {
            temp->getNext()->setPrev(temp->getPrev());
        }
        else
        {
            last = temp->getPrev();
        }
        if (temp->getPrev())
        {
            temp->getPrev()->setNext(temp->getNext());
        }
        else
        {
            first = temp->getNext();
        }
        delete temp;
        temp = nullptr;

        --count;
    }

    inline void swapNodes(Node<T>& node1, Node<T>& node2) const
	{
		std::swap(node1.getData(), node2.getData());
	}

	void sort()
	{
		quickSort(first, last);
	}

    List<T>& operator=(List<T>&& other) noexcept
	{
		if (this != &other)
		{
			first = other.first;
			last = other.last;
			count = other.count;
			other.first = nullptr;
			other.last = nullptr;
		}

		return *this;
    }

    List<T>& operator=(const List<T>& other)
    {
        first = other.first;
        last = other.last;
        count = other.count;
        return *this;
    };
};
