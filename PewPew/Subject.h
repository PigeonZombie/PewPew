#pragma once
#include "IObserver.h"
#include <vector>
#include <algorithm>
#include <typeindex>

using std::vector;

//class Joueur;

class Subject
{
protected:
	static vector<IObserver*> observers;
	static vector<IObserver*> armeObservers;

public:
	static void CreerArmeObservers(IObserver* _ob1, IObserver* _ob2);
	static void Add_Observer(IObserver* _observer);
	static void Remove_Observer(IObserver* _observer);
	virtual void Notify_Observers(bool _isArme, bool _isFromShot = false, std::type_index* _typeIdJoueur = nullptr);  //Virtuel seulement pour que typeID fonctionne avec typeid
};