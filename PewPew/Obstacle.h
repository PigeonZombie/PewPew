// Classe qui g�re les ast�ro�des 
#pragma once
#include <SFML/Graphics.hpp>
#include "Constante.h"
#include "IObserver.h"
#include "Vaisseau.h"
#include "BombeExplo.h"
using namespace sf;
namespace PewPew
{
	class Obstacle : public Sprite, public IObserver
	{
	public:
		// Constructeur et destructeur 
		Obstacle();
		~Obstacle();
		// M�thode de l'observateur
		void Notify(Subject* _subject);
		// Charge toutes les textures 
		static bool Init();
		// D�placement des ast�ro�des 
		void Move();
		// D�finit si l'objet est dans les limites du jeu
		bool EstDansLeJeu() const;
		// V�rifie les collisions avec les ennemis et le joueur
		bool VerifierCollision(Vaisseau* vaisseau);
	private:
		// Les 5 textures possible pour les obstacles
		static Texture t[NB_MAX_OBSTACLE];
		// La direction de l'obstacle
		Vector2f mouvement;
		// D�finit si l'objet est dans les limites du jeu
		bool estDansLeJeu;
		// Retourne un direction al�atoire en X ou en Y
		float GetRandomDirection(float min, float max);
		// D�finit si l'objet est destructible ou non
		bool destructible; 
	};
}


