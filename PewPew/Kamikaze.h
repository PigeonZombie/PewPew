// Classe du vaisseau Kamikaze
#pragma once
#include "Ennemi.h"
namespace PewPew
{
	class Kamikaze:public Ennemi
	{
	public:
		// Constructeur et destructeur
		Kamikaze();
		~Kamikaze();
		// Mouvement du vaisseau
		void Mouvement(Vector2f target);
		void Mouvement();
		// Méthode de tir
		Tir* tirer();
		// Place la texture dans le sprite
		void InitGraphiques();
	};
}
