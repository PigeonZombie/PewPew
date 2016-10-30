#pragma once
#include "Arme.h"

namespace PewPew
{
	class ArmeNormal : public Arme
	{
	public:
		ArmeNormal(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active);

		void InitGraphiques();
		void Action();		
		Tir* Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player = false);
	};
}