#pragma once
#include "Node.h"

namespace myns
{
	template<class _type>
	class List
	{
	public:		
		List<_type>();		
		~List<_type>();
		bool Add(_type *_element, int _index = 0);		
		bool Remove(int _index = 0);		
		Node<_type>& operator[](int const& _i);
		Node<_type>& overload(int const& _index);		
		int GetSize() const;

	private:
		int size;
		Node<_type>* firstNode;
	};
}

/// <summary>
/// Initialize a new instance of a list. Puts the pointer to the first node at NULL.
/// </summary>
template<class _type>
myns::List<_type>::List()
{
	this->size = 0;
	this->firstNode = nullptr;
}

/// <summary>
/// Delete all nodes form the list. Does not delete the contents of those nodes.
/// </summary>
template<class _type>
myns::List<_type>::~List()
{
	Node<_type>* tNode = this->firstNode;
	while (tNode != nullptr)
	{
		Node<_type>* nTR = tNode;
		tNode = tNode->GetNext();
		delete nTR;
	}
}

/// <summary>
/// Adds a new node at the specified index. If no index is specified, it adds the element at index 0.
/// </summary>
/// <param name="_element">The content to be added.</param>
/// <param name="_index">The index where to add the content.</param>
/// <returns>returns false is the specified index is out of range. Else returns true.</returns>
template<class _type>
bool myns::List<_type>::Add(_type *_element, int _index)
{
	Node<_type>* nn = new Node<_type>(nullptr, _element);
	Node<_type>* tNode = this->firstNode;
	if (_index == 0 || this->firstNode == nullptr)
	{
		nn->SetNext(this->firstNode);
		this->firstNode = nn;
		this->size++;
		return true;
	}
	for (int i = 0; i < (_index - 1); i++)
	{
		tNode = tNode->GetNext();
		if (tNode == nullptr)
		{
			return false;
		}
	}
	if (tNode != nullptr)
	{
		nn->SetNext(tNode->GetNext());
		tNode->GetNext();
	}
	this->size++;
	return true;
}

/// <summary>
/// Removes element at the specified index. If no index is specified, the first element is removed.
/// </summary>
/// <param name="_index">The index at wich the element should be removed.</param>
/// <returns>Returns false if the index is out of range. Else returns true.</returns>
template<class _type>
bool myns::List<_type>::Remove(int _index)
{
	Node<_type>* tNode = this->firstNode;
	if (_index == 0)
	{
		Node<_type>* NAE = this->firstNode;
		this->firstNode = this->firstNode->GetNext();
		delete NAE;
		this->size--;
		return true;
	}
	for (int i = 0; i < (_index - 1); i++)
	{
		tNode = tNode->GetNext();
		if (tNode == nullptr)
		{
			return false;
		}
	}
	Node<_type>* toDelete = tNode->GetNext();
	tNode->SetNext(toDelete->GetNext());
	delete toDelete;
	this->size--;
	return true;

}

/// See the operator overlaod description.
template<class _type>
myns::Node<_type>& myns::List<_type>::overload(int const& _index)
{
	Node<_type>* tNode = this->firstNode;
	for (int i = 0; i < _index; i++)
	{
		tNode = tNode->GetNext();
	}
	return *tNode;
}

/// <summary>
/// Returns the node at the index specified between the [].
/// </summary>
/// <param name="_index">The index of the wanted node.</param>
/// <returns>Returns the node at the index specified between the [].</returns>
template<class _type>
myns::Node<_type>& myns::List<_type>::operator[](int const& _i)
{
	return this->overload(_i);
}

/// <summary>
/// Gets the number of elements in the list. The size is incremented when the "Add" function is called
/// and decremented when the "Remove" function is called.
/// </summary>
/// <returns>Returns an int representing the number of elements int the list.</returns>
template<class _type>
int myns::List<_type>::GetSize() const
{
	return this->size;
}