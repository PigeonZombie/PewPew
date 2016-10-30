#pragma once
#include "TirNormal.h"
#include "List.h"

namespace PewPew
{
	class TirEvantail : public Tir
	{
	private:
		int nbTirs; //Nombre de tirs.
		myns::List<TirNormal> tirs; //Contient tous les tirs.
		myns::List<sf::Vector2f> angles; //Contient tous les angle dans lesquel effectuer les tirs.

	public:
		TirEvantail();
		TirEvantail(sf::Vector2f* _position, int _nbTirs, int _puissance = 0, float _vitesse = 0, int _rotation = 0, bool _joueur = false);
		~TirEvantail();		
		int Init(sf::Texture &_texture);		
		void InitAngles();		
		sf::Vector2f* RotateVector(sf::Vector2f &_vector, float _rotation);
		void Move();		
		bool VerifierCollision(Vaisseau* _ship);
		void Draw(sf::RenderWindow &_window);
	};
}