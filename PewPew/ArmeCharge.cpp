#include "ArmeCharge.h"

using namespace PewPew;

ArmeCharge::ArmeCharge(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active) : 
	Arme(_typeTir, _cadence, _munitions, _position, _active)
{

}

void ArmeCharge::InitGraphiques()
{
	this->setTexture(tArmeCharge);
}

void ArmeCharge::Action()
{
	this->Notify_Observers(true);
}

/// <summary>
/// Effectu un tir du type de l'arme.
/// </summary>
/// <param name="_p">Position du tir.</param>
/// <param name="_d">Direction du tir.</param>
/// <param name="_player">Vrai si c'est un tir qui vient du joueur. Faux sinon.</param>
/// <returns>Retourne le tir.</returns>
Tir* ArmeCharge::Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player)
{
	//Si l'arme est en mesure de tirer et qu'il reste encore des munitions,
	if (this->peutTirer == 0 && this->munitions > 0)
	{
		//remttre l'arme en coldown,
		this->peutTirer = this->CADENCE_TIR;
		//Enlever une munition,
		this->munitions--;
		isCharging = false;
		//Créer le tir.
		return TirFactory::CreerTir(_p, _d, 3, 10, 0, nullptr, this->TYPE_TIR, _player);
	}
	//Sinon,
	else
	{
		//delete les vecteurs
		delete _p;
		delete _d;
	}
	//et retourner nullptr.
	return nullptr;
}

bool ArmeCharge::IsCharging() const
{
	return this->isCharging;
}

void ArmeCharge::SetIsCharging(bool _value)
{
	this->isCharging = _value;
}