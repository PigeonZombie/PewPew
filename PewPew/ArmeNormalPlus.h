#pragma once
#include "ArmeNormal.h"

namespace PewPew
{
	class ArmeNormalPlus : public Arme
	{
	public:
		ArmeNormalPlus(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active);

		void InitGraphiques();
		void Action();		
		Tir* Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player = false);
	};
}