#include "Subject.h"
#include <exception>
#include <iostream>
#include "Joueur.h"

vector<IObserver*> Subject::observers;
vector<IObserver*> Subject::armeObservers;

void Subject::Add_Observer(IObserver* _observer)
{
	//Si l'observateur n'est pas déjà dans la liste...
	if (!(std::find(observers.begin(), observers.end(), _observer) != observers.end()))
	{
		observers.push_back(_observer);
	}
}

void Subject::Remove_Observer(IObserver* _observer)
{
	//Pour retirer un observateur de la liste. 
	//Deux pointeurs qui pointent à la même adresse sont égaux.
	for (int i = 0; i < observers.size(); i++)
	{
		if (observers[i] == _observer)
		{
			observers.erase(observers.begin() + i);
			return;
		}
	}
}

//Suite à une action on fait toujours ça.
void Subject::Notify_Observers(bool _isArme, bool _isFromShot, std::type_index* _typeIdJoueur)
{
	if (!_isArme)
	{
		for (int i = 0; i < this->observers.size(); i++)
		{
			if (observers[i] != nullptr)
			{
				this->observers[i]->Notify(this);
			}
			else
			{
				Remove_Observer(this->observers[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < this->armeObservers.size(); i++)
		{
			if (armeObservers[i] != nullptr)
			{
				if (_isFromShot)
				{
					if (!(std::type_index(typeid(*armeObservers[i])) == *_typeIdJoueur))
					{
						this->armeObservers[i]->Notify(this);
					}
				}
				else
					this->armeObservers[i]->Notify(this);
			}
		}
	}
}

void Subject::CreerArmeObservers(IObserver* _ob1, IObserver* _ob2)
{
	armeObservers.push_back(_ob1);
	armeObservers.push_back(_ob2);
}