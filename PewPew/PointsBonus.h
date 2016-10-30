#pragma once
#include <SFML\Graphics.hpp>
#include "Bonus.h"
using namespace sf;
namespace PewPew
{
	class PointsBonus:public Bonus
	{
	public:
		// Constructeur et destructeur
		PointsBonus(Vector2f position);
		~PointsBonus();
		// Place la texture dans le sprite
		void InitGraphiques();
		// Déclenche l'action du point bonus 
		void Action();
		// Obtient la valeur du bonus
		int GetValeur() const;
	private:
		// La valeur du bonus
		int value;
	};
}
