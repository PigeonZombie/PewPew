// Classe qui gère le bonus de bombe explosive
#pragma once
#include "Bonus.h"
namespace PewPew
{
	class BombeExplo :public Bonus
	{
	public:
		// Constructeur et destructeur
		BombeExplo(Vector2f position);
		~BombeExplo();
		// Place la texture dans le Sprite
		void InitGraphiques();
		// Déclenche le cycle de destruction de la bombe 
		void Action();
		//IntRect& GetCadre();
		Color GetColor() const;
	private:
		// Le rectangle englobant la bombe
		IntRect cadreBombe;
		// Variables pour gérer l'animation 
		int step;
		int animation;
		const int ANIMATION_MAXIMALE = 120;
		// La taille de la bombe
		Vector2f size;
		// La couleur de la bombe
		Color couleur;
	};
}
