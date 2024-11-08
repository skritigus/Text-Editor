#pragma once

#include "Node.h"
#include <iostream>

template <typename T>
class ListIterator
{
	Node<T>* ptr;

public:
	using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit ListIterator(Node<T>* ptr) : ptr(ptr) {}

	ListIterator(const ListIterator<T>& iterator) = default;

	ListIterator<T>& operator=(const ListIterator<T>& iterator) = default;

	ListIterator<T>& operator=(Node<T>* otherPtr)
	{
		ptr = otherPtr;
		return (*this);
	};

	explicit operator bool() const
	{
		if (ptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    bool operator==(ListIterator<T>& iterator)
    {
        return ptr == iterator.getPtr();
    }

	ListIterator<T>& operator++()
	{
		ptr = ptr->getNext();
		return (*this);
	}

	ListIterator<T>& operator--()
	{
		ptr = ptr->getPrev();
		return (*this);
	}

	ListIterator<T> operator++(int)
	{
		auto temp(*this);
		ptr = ptr->GetNext();
		return temp;
	}

	ListIterator<T> operator--(int)
	{
		auto temp(*this);
		ptr = ptr->getPrev();
		return temp;
	}

    Node<T>& operator*()
	{
		return *ptr;
	}

    Node<T>& operator*() const
	{
		return *ptr;
	}

    Node<T>* operator->()
	{
		return ptr;
	}

    Node<T>* getPtr()
	{
		return ptr;
	}

};
