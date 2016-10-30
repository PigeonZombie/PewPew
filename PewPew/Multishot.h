// Classe du vaisseau Multishot
#pragma once
#include "Ennemi.h"
namespace PewPew
{
	class Multishot :public Ennemi
	{
	public:
		// Constructeur et destructeur
		Multishot();
		~Multishot();
		// Méthode de déplacement
		void Mouvement();
		// Méthodes de tir
		Tir* tirer();
		Tir* tirer(int _k);
		// Place la texture dans le sprite
		void InitGraphiques();
	private:
		// Le vecteur de déplacement du vaisseau
		Vector2f mouvement;
	};
}

