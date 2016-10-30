#pragma once
#include "TirNormal.h"

namespace PewPew
{
	class TirChercheur : public TirNormal
	{
	private:
		Vaisseau* cible; //Cible qui le tir cherche à atteindre.

	public:
		TirChercheur();
		TirChercheur(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance = 0, float _vitesse = 0, int _rotation = 0, Vaisseau* _cible = nullptr,bool _joueur=false);
		~TirChercheur();
		int Init(sf::Texture &_texture);		
		void Move();

		void SetCible(Vaisseau* _newCible);
		Vaisseau* GetCible() const;
	};
}