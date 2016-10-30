#pragma once
#include "TirChercheur.h"
#include "TirEvantail.h"
#include "TirCharge.h"

namespace PewPew
{
	class TirFactory
	{
	public:		
		static Tir* CreerTir(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance = 0, float _vitesse = 0, int _rotation = 0, Vaisseau* _cible = nullptr, int _type = 0, bool _joueur = false, int _nbTirs = 0);
	
	private:
		//Ne contient qu'une méthode static, ne doit pas être instancié.
		TirFactory();
	};
}