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
		// M�thode de d�placement
		void Mouvement();
		// M�thodes de tir
		Tir* tirer();
		Tir* tirer(int _k);
		// Place la texture dans le sprite
		void InitGraphiques();
	private:
		// Le vecteur de d�placement du vaisseau
		Vector2f mouvement;
	};
}

