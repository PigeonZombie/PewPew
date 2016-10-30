#define _USE_MATH_DEFINES
#include "ArmeTriangle.h"
#include <math.h>

using namespace PewPew;

ArmeTriangle::ArmeTriangle(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active, int _nbAngles) :
	Arme(_typeTir, _cadence, _munitions, _position, _active),
	NB_ANLGES(_nbAngles)
{

}

void ArmeTriangle::InitGraphiques()
{
	setTexture(tArmeTriangle);
}
void ArmeTriangle::Action()
{
	this->Notify_Observers(true);
	actif = false;
}

/// <summary>
/// Effectu un tir du type de l'arme.
/// </summary>
/// <param name="_p">Position du tir.</param>
/// <param name="_d">Direction du tir.</param>
/// <param name="_player">Vrai si c'est un tir qui vient du joueur. Faux sinon.</param>
/// <returns>Retourne le tir.</returns>
Tir* ArmeTriangle::Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player)
{
	//Voir commentaire de ArmeCharge...
	if (this->peutTirer == 0 && this->munitions > 0)
	{
		this->peutTirer = this->CADENCE_TIR;
		this->munitions--;
		//Un TirEvantail ne doit jamais avoir une direction de spécifiée, donc si c'est le cas, le vecteur de direction spécifié est delete.
		if (_d != nullptr)
			delete _d;
		return TirFactory::CreerTir(_p, nullptr, 1, 7, 0, nullptr, 2, _player, this->NB_ANLGES);
	}
	else
	{
		delete _p;
		//It should be, but we never know...
		if (_d != nullptr)
			delete _d;
	}
	return nullptr;
}

int ArmeTriangle::GetNbAngles() const
{
	return this->NB_ANLGES;
}