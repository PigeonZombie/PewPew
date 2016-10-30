// Classe du vaisseau de Base Am�lior�. H�rite du vaisseau de Base
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
		// D�placement du vaisseau
		void Mouvement(Vector2f target);
		// Tir du vaisseau
		Tir* tirer();
		// Place la texture dans le sprite
		void InitGraphiques();
	};
}

