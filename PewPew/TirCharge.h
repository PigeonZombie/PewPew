#pragma once
#include "Tir.h"
#include "Vaisseau.h"

namespace PewPew
{
	class Vaisseau;
	//Tir qui peut être chargé pour faire plus de dégâts.
	class TirCharge : public Tir
	{
	public:
		TirCharge(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance = 0, float _vitesse = 0, int _rotation = 0, bool _joueur = false);
		~TirCharge();
		int Init(sf::Texture &_texture);
		void Move();		
		bool Move(Vaisseau* _vaisseau);
		bool VerifierCollision(Vaisseau* _ship);		
		void UpdateCharge();		
		void Shoot();
		bool IsShot() const;
		int GetCharge() const;

	private:
		int charge;
		const int CHARGE_MAX = 180; //Temps maximum pendant lequel le tir peut être chargé.
		bool isShot;
	};
}