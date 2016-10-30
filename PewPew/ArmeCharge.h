#pragma once
#include "Arme.h"

namespace PewPew
{
	class ArmeCharge : public Arme
	{
	public:
		ArmeCharge(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active);
		void InitGraphiques();
		void Action();		
		Tir* Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player = false);

		bool IsCharging() const;
		void SetIsCharging(bool _value);

	private:
		bool isCharging; //Vrai si l'arme est en train de charger un tir. Faux sinon.
	};
}