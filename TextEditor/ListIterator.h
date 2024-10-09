#pragma once

template <typename T>
class ListIterator
{
	Node<T>* ptr;
public:
	using iterator_concept = std::bidirectional_iterator_tag;

	explicit ListIterator(Node<T>* ptr)
	{
		this->ptr = ptr;
	}

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

	bool operator==(const ListIterator<T>& iterator) const = default;

	ListIterator<T>& operator++()
	{
		ptr = ptr->GetNext();
		return (*this);
	}

	ListIterator<T>& operator--()
	{
		ptr = ptr->GetPrev();
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
		ptr = ptr->GetPrev();
		return temp;
	}

	Node<T>& operator*()
	{
		return *ptr;
	}

	const Node<T>& operator*() const
	{
		return *ptr;
	}

	Node<T>* operator->()
	{
		return ptr;
	}

	Node<T>* GetPtr()
	{
		return ptr;
	}
};

