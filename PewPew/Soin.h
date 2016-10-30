#pragma once
#include <SFML\Graphics.hpp>
#include "Bonus.h"
using namespace sf;

namespace PewPew
{
	class Soin:public Bonus
	{
	public:
		// Constructeur et destructeur
		Soin(Vector2f position);
		~Soin();
		// Place la texture dans le sprite
		void InitGraphiques();
		// Déclenche l'action du bonus
		void Action();
	};
}


