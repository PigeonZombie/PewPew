#pragma once
#include "Arme.h"
#include "List.h"

namespace PewPew
{
	class ArmeTriangle : public Arme
	{
	public:
		ArmeTriangle(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active, int _nbAngles);

		void InitGraphiques();
		void Action();		
		Tir* Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player = false);

		int GetNbAngles() const;

	private:
		const int NB_ANLGES; //Nombre d'angle que doivent avoir les tirs de cette arme.
	};
}