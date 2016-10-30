#pragma once

namespace myns
{
	template<typename T>
	class Node
	{
	public:
		Node<T>::Node(Node<T>* _next, T* _element); //Constructeur, initialise les variable aus paramètre passés à la fonction.
		Node<T>* GetNext(); //Retourne le Node qui suit dans la pile.
		void SetNext(Node<T>* _Node); //Redéfinir le Node qui suit dans la pile. **Note : ne crée pas un nouveau Node.
		T* GetContent();				//Renvoie l'adresse qui contient le contenue du Node.
		void SetContent(T* _element);	//Redéfénie le contenue pointer par le Node.

	private:
		Node* next; //Pointeur vers le Node qui suit dans le pile. Si c'est le dernier Node, ponte vers nullptr.
		T* element; //Pointeur vers le contenue
	};
}

template<typename T>
myns::Node<T>::Node(Node<T>* _next, T* _element) :
	next(_next),
	element(_element)
{
	
}

//Get

template<typename T>
myns::Node<T>* myns::Node<T>::GetNext()
{
	return this->next;
}

template<typename T>
T* myns::Node<T>::GetContent()
{
	return this->element;
}

//Set

template<typename T>
void myns::Node<T>::SetNext(Node<T>* _Node)
{
	this->next = _Node;
}

template<typename T>
void myns::Node<T>::SetContent(T* _element)
{
	this->element = _element;
}