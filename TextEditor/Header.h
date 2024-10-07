#pragma once
#pragma once

template <typename T>
class Iterator
{
	T* ptr;
public:
	explicit Iterator(T* ptr)
	{
		this->ptr = ptr;
	}

	Iterator(const Iterator<T>& iterator) = default;

	Iterator<T>& operator=(const Iterator<T>& iterator) = default;

	Iterator<T>& operator=(T* otherPtr)
	{
		ptr = otherPtr;
		return (*this);
	};

	explicit operator bool()const
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

	bool operator==(const Iterator& iterator)const
	{
		return this->ptr == iterator.ptr;
	}

	bool operator!=(const Iterator& iterator)const
	{
		return !operator==(iterator);
	}

	Iterator<T>& operator+=(const int& offset)
	{
		ptr += offset;
		return (*this);
	}

	Iterator<T>& operator-=(const int& offset)
	{
		ptr -= offset;
		return (*this);
	}

	Iterator<T>& operator++()
	{
		++ptr;
		return (*this);
	}

	Iterator<T>& operator--()
	{
		--ptr;
		return (*this);
	}

	Iterator<T> operator++(int)
	{
		auto temp(*this);
		++ptr;
		return temp;
	}

	Iterator<T> operator+(const int& offset)
	{
		auto temp(*this);
		temp.ptr += offset;
		return temp;
	}

	Iterator<T> operator-(const int& offset)
	{
		auto temp(*this);
		temp.ptr -= offset;
		return temp;
	}

	int operator-(const Iterator<T>& iterator)
	{
		auto temp(*this);
		temp.ptr -= iterator.ptr;
		return static_cast<int>(temp.ptr);
	}

	T& operator*()
	{
		return *ptr;
	}

	//const T& operator*()const
	//{
	//	return *ptr;
	//}

	T* operator->()
	{
		return ptr;
	}

	T* GetPtr()
	{
		return ptr;
	}
};

template <typename T>
class ReverseIterator
{
	T* ptr;
public:
	explicit ReverseIterator(T* ptr)
	{
		this->ptr = ptr;
	}

	ReverseIterator(const ReverseIterator<T>& iterator) = default;

	ReverseIterator<T>& operator=(const ReverseIterator<T>& iterator) = default;

	ReverseIterator<T>& operator=(T* otherPtr)
	{
		ptr = otherPtr;
		return (*this);
	};

	explicit operator bool()const
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

	bool operator==(const ReverseIterator& iterator)const
	{
		return this->ptr == iterator.ptr;
	}

	bool operator!=(const ReverseIterator& iterator)const
	{
		return !operator==(iterator);
	}

	ReverseIterator<T>& operator+=(const int& offset)
	{
		ptr -= offset;
		return (*this);
	}

	ReverseIterator<T>& operator-=(const int& offset)
	{
		ptr += offset;
		return (*this);
	}

	ReverseIterator<T>& operator++()
	{
		--ptr;
		return (*this);
	}

	ReverseIterator<T>& operator--()
	{
		++ptr;
		return (*this);
	}

	ReverseIterator<T> operator++(int)
	{
		auto temp(*this);
		--ptr;
		return temp;
	}

	ReverseIterator<T> operator+(const int& offset)
	{
		auto temp(*this);
		temp.ptr -= offset;
		return temp;
	}

	ReverseIterator<T> operator-(const int& offset)
	{
		auto temp(*this);
		temp.ptr += offset;
		return temp;
	}

	int operator-(const ReverseIterator<T>& iterator)
	{
		auto temp(*this);
		temp.ptr += iterator.ptr;
		return static_cast<int>(temp.ptr);
	}

	T& operator*()
	{
		return *ptr;
	}

	//const T& operator*()const
	//{
	//	return *ptr;
	//}

	T* operator->()
	{
		return ptr;
	}

	T* GetPtr()
	{
		return ptr;
	}
};