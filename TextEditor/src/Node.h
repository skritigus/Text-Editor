#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
	T data;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;

public:
    Node() = default;
    explicit Node(const T& data) : data(data) {}

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

    void setData(const T& newData)
	{
		data = newData;
	}

    bool operator==(const Node<T>& node)
	{
		return data == node.getData();
	}

    auto operator<=>(const Node<T>& node)
	{
        return data <=> node.getData();
    }
};

#endif
