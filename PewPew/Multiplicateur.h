#pragma once
#include <SFML\Graphics.hpp>
#include "Bonus.h"
using namespace sf;
namespace PewPew
{
	class Multiplicateur:public Bonus
	{
	public:
		// Constructeur et destructeur
		Multiplicateur(Vector2f position);
		~Multiplicateur();
		// Place la texture dans le sprite
		void InitGraphiques();
		// Déclenche l'action du multiplicateur
		void Action();
	private:
		// Le temps de duration du multiplicateur
		int frameDuration;
		// Le nombre de frames écoulés depuis l'activation
		int frames;
	};
}


