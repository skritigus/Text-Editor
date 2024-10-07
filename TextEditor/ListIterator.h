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

	bool operator==(const ListIterator& iterator) const
	{
		return this->ptr == iterator.ptr;
	}

	bool operator!=(const ListIterator& iterator) const
	{
		return !operator == (iterator);
	}

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

template <typename T>
class ReverseListIterator
{
	Node<T>* ptr;
public:
	using iterator_concept = std::bidirectional_iterator_tag;

	explicit ReverseListIterator(Node<T>* ptr)
	{
		this->ptr = ptr;
	}

	ReverseListIterator(const ReverseListIterator<T>& iterator) = default;

	ReverseListIterator<T>& operator=(const ReverseListIterator<T>& iterator) = default;

	ReverseListIterator<T>& operator=(Node<T>* otherPtr)
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

	bool operator==(const ReverseListIterator& iterator) const
	{
		return this->ptr == iterator.ptr;
	}

	bool operator!=(const ReverseListIterator& iterator) const
	{
		return !operator == (iterator);
	}

	ReverseListIterator<T>& operator+=(const int& offset)
	{
		for (int i = 0; i < offset; ++i)
		{
			--(*this);
		}
		return (*this);
	}

	ReverseListIterator<T>& operator-=(const int& offset)
	{
		for (int i = 0; i < offset; ++i)
		{
			++(*this);
		}
		return (*this);
	}

	ReverseListIterator<T>& operator++()
	{
		ptr = ptr->GetPrev();
		return (*this);
	}

	ReverseListIterator<T>& operator--()
	{
		ptr = ptr->GetNext();
		return (*this);
	}

	ReverseListIterator<T> operator++(int)
	{
		auto temp(*this);
		ptr = ptr->GetPrev();
		return temp;
	}

	ReverseListIterator<T> operator--(int)
	{
		auto temp(*this);
		ptr = ptr->GetNext();
		return temp;
	}

	ReverseListIterator<T> operator+(const int& offset)
	{
		auto temp(*this);
		for (int i = 0; i < offset; ++i)
		{
			--(*this);
		}
		return temp;
	}

	ReverseListIterator<T> operator-(const int& offset)
	{
		auto temp(*this);
		for (int i = 0; i < offset; ++i)
		{
			++(*this);
		}
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
