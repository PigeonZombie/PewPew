// Classe qui g�re la bombe magn�tique emp�chant les ennemis de tirer
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
		// D�clenche le cycle d'explosion de la bombe 
		void Action();
	private:
		// Rectangle d'animation
		IntRect cadreBombe;
		// Variables qui g�rent l'animation de la bombe
		int step;
		int animation;
		const int ANIMATION_MAXIMALE = 120;
		// Taille de la bombe
		Vector2f size;
	};
}

