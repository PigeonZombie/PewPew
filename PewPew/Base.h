// Classe du vaisseau de base 
#pragma once
#include "Ennemi.h"
namespace PewPew
{
	class Base : public Ennemi
	{
	public:
		// Constructeur et destructeur
		Base();
		~Base();
		// Déplacement du vaisseau
		virtual void Mouvement();
		// Tir du vaisseau
		virtual Tir* tirer();
		// Placer la texture dans le sprite
		virtual void InitGraphiques();
	private:

	};
}


