// Classe qui gère les boucliers du joueur 
#pragma once
#include "Bonus.h"

namespace PewPew
{
	class Bouclier :public Bonus
	{
	public:
		// Constructeur et destructeur
		Bouclier(Vector2f position);
		~Bouclier();
		// Place la texture dans le sprite
		void InitGraphiques();
		// Déclenche l'action du bouclier
		void Action();
		// Obtient la couleur du bouclier
		Color GetColor() const;
		// Retourne le cercle qui représente le bouclier 
		CircleShape GetShape() const;
		// Change le position du cercle pour suivre le vaisseau du joueur
		void SetPosition(const Vector2f position);
		// Retourne le nombre de points de vie restant au bouclier
		int GetPV() const;
		// Enlève des points de vie au bouclier
		void InfligerDegats(int degats);
	private:
		// La couleur du bouclier (rouge,bleu ou vert)
		Color color;
		// Le cercle qui représente le bouclier
		CircleShape shape;
		// La résistance du bouclier
		int pointsVie;
	};
}


