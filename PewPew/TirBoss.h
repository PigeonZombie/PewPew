#pragma once
#include "Tir.h"
#include "List.h"

namespace PewPew
{
	class Ennemi;

	class TirBoss : public Tir
	{
	public:
		TirBoss(sf::Vector2f* _position);
		~TirBoss();
		int Init(sf::Texture &_texture); //Initialise tous les tirs contenus dans la liste de tirs.
		void Move(); //D�place tous les tirs dans la liste de tirs.
		bool VerifierCollision(Vaisseau* _ship); //V�rifie la collision de tous les tirs dans la liste de tirs avec le vaisseau pass� en param�tre.		
		void AjouterTirs(Ennemi* _boss, Vaisseau* _cible = nullptr); //Ajoute un tir � la liste de tires.
		void Draw(sf::RenderWindow &_window); //Dessine tous les tirs de la liste de tirs dans la fen�tre pass�e en param�tre.

	private:
		myns::List<Tir> tirs; //La fameuse liste de tirs.
	};
}