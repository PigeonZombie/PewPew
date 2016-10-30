// Classe qui gère la bombe magnétique empêchant les ennemis de tirer
#pragma once
#include "Bonus.h"

namespace PewPew
{
	class BombeMagnetique:public Bonus
	{
	public:
		// Constructeur et destructeur 
		BombeMagnetique(Vector2f position);
		~BombeMagnetique();
		// Place la texture dans le sprite
		void InitGraphiques();
		// Déclenche le cycle d'explosion de la bombe 
		void Action();
	private:
		// Rectangle d'animation
		IntRect cadreBombe;
		// Variables qui gèrent l'animation de la bombe
		int step;
		int animation;
		const int ANIMATION_MAXIMALE = 120;
		// Taille de la bombe
		Vector2f size;
	};
}

