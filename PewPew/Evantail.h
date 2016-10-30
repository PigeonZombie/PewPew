// Classe du vaisseau évantail 
#pragma once
#include "Ennemi.h"
namespace PewPew
{
	class Evantail:public Ennemi
	{
	private:

	public:
		// Constructeur et destructeur
		Evantail();
		~Evantail();
		// Mouvement du vaisseau
		void Mouvement();
		// Tir du vaisseau
		Tir* tirer();
		Tir* tirer(int _k);
		// Placer la texture dans le sprite
		void InitGraphiques();
		// Le nombre de projectiles tirés par le vaisseau en un coup
		static const int NB_SHOTS = 7;
		// Détermine les directions des projectiles
		static void InitDirections();
		// Les directions des projectiles
		static Vector2f* directions[NB_SHOTS];
		// Effectue une rotation d'un vecteur
		static Vector2f* RotateVector(Vector2f &_vector, float _rotation);
	};
}
