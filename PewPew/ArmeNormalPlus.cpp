#include "ArmeNormalPlus.h"

using namespace PewPew;

ArmeNormalPlus::ArmeNormalPlus(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active) :
	Arme(_typeTir, _cadence, _munitions, _position, _active)
{

}

/// <summary>
/// Effectu un tir du type de l'arme.
/// </summary>
/// <param name="_p">Position du tir.</param>
/// <param name="_d">Direction du tir.</param>
/// <param name="_player">Vrai si c'est un tir qui vient du joueur. Faux sinon.</param>
/// <returns>Retourne le tir.</returns>
Tir* ArmeNormalPlus::Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player)
{
	//Voir commentaire de ArmeCharge...
	if (this->peutTirer == 0 && this->munitions > 0)
	{
		this->peutTirer = this->CADENCE_TIR;
		this->munitions--;
		return TirFactory::CreerTir(_p, _d, 2, 10, 0, nullptr, this->TYPE_TIR, _player);
	}
	else
	{
		delete _p;
		delete _d;
	}
	return nullptr;
}

void ArmeNormalPlus::InitGraphiques()
{
	setTexture(tArmeNormalPlus);
}

void ArmeNormalPlus::Action()
{
	this->Notify_Observers(true);
}