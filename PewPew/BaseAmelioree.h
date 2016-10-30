// Classe du vaisseau de Base Amélioré. Hérite du vaisseau de Base
#pragma once
#include "Base.h"

namespace PewPew
{
	class BaseAmelioree: public Base
	{
	public:
		// Constructeur et destructeur
		BaseAmelioree();
		~BaseAmelioree();
		// Déplacement du vaisseau
		void Mouvement(Vector2f target);
		// Tir du vaisseau
		Tir* tirer();
		// Place la texture dans le sprite
		void InitGraphiques();
	};
}

