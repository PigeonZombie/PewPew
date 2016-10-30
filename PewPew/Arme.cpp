#include "Arme.h"

using namespace PewPew;

Arme::Arme(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active) :
	Bonus(_position, true),
	TYPE_TIR(_typeTir),
	CADENCE_TIR(_cadence),
	peutTirer(0),
	munitions(_munitions),
	active(_active)
{

}

/// <summary>
/// Effectu un tir du type de l'arme.
/// </summary>
/// <param name="_p">Position du tir.</param>
/// <param name="_d">Direction du tir.</param>
/// <param name="_player">Vrai si c'est un tir qui vient du joueur. Faux sinon.</param>
/// <returns>Retourne le tir.</returns>
Tir* Arme::Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player)
{
	delete _p;
	delete _d;
	return nullptr;
}

void Arme::InitGraphiques()
{

}

void Arme::Action()
{

}

int Arme::GetMunitions() const
{
	return this->munitions;
}

bool Arme::IsActive() const
{
	return this->active;
}

void Arme::SetActive(bool _value)
{
	this->active = _value;
}

void Arme::SetPeutTirer()
{
	if (this->peutTirer > 0)
		this->peutTirer--;
}

void Arme::SetMunitions(int _value)
{
	this->munitions = _value;
}