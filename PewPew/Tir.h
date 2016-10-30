#pragma once
#include <SFML\Graphics.hpp>
#include "Subject.h"

namespace PewPew
{
	class Vaisseau;

	class Tir : public sf::Sprite, public Subject
	{
	protected:
		sf::Vector2f* direction; //Indique la direction dans laquelle le tir se dirige.
		sf::Vector2f* position;
		int puissance; //Nombre de d�g�ts inflig�s par le tir.
		float vitesse; //Vitesse du tir.
		int rotation;
		bool joueur; //true si c'est un tir du joueur, false sinon.
		bool toDelete; //true si le tir est � retirer du jeux (Note : n'est utilis�e que dans TirEvantail, pour tous les autres tirs, elle vaut true en permanance).
		sf::Color couleur; //Couleur du tir.
		sf::Texture textureTir;

	public:
		Tir();
		Tir(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance = 0, float _vitesse = 0, int _rotation = 0, bool _joueur = false);
		virtual ~Tir() = 0;
		virtual int Init(sf::Texture &_texture) = 0; //Initialise le tir apr�s avoir �t� construit.
		virtual void Move() = 0; //D�place le tir dans l'espace (quel beau jeu de mots!).		
		virtual bool VerifierCollision(Vaisseau* _ship); //V�rifie la collision avec le vaisseau pass� en param�tre.
		bool VientDuJoueur() const;
		bool ToDelete() const;
	};
}