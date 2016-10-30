#pragma once
#include "Node.h"

namespace myns
{
	template<typename T>
	class Pile
	{
	public:
		Pile<T>(); //Constructeur, initialise FirstNode à nullptr.
		~Pile<T>(); //Destructeur, delete tous les Nodes.

		void Push(T* _element); //Ajouter un Node à la pile.
		T* Pop(); //Supprime le premier élément de la pile et renvoie sont contenue.

		Node<T>* GetFirstNode() const; //Retourne le premier Node de la pile, sans la modifier.

	private:
		Node<T>* FirstNode; //Premier élément de la pile.
	};
}



template<typename T>
myns::Pile<T>::Pile()
{
	this->FirstNode = nullptr;
}

template<typename T>
myns::Pile<T>::~Pile()
{
	while (this->FirstNode != nullptr)
	{
		this->Pop();
	}
}

template<typename T>
void myns::Pile<T>::Push(T* _element)
{
	Node<T>* newNode = new Node<T>(this->FirstNode, _element);
	this->FirstNode = newNode;
}

template<typename T>
T* myns::Pile<T>::Pop()
{
	T* Content = nullptr;

	if (this->FirstNode != nullptr)
	{
		Content = this->FirstNode->GetContent();
		Node<T>* tempNode = this->FirstNode;
		this->FirstNode = this->FirstNode->GetNext();
		delete tempNode;
	}
	return Content;
}

template<typename T>
myns::Node<T>* myns::Pile<T>::GetFirstNode() const
{
	return this->FirstNode;
}