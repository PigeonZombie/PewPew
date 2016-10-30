// Classe qui gère les astéroïdes 
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
		// Méthode de l'observateur
		void Notify(Subject* _subject);
		// Charge toutes les textures 
		static bool Init();
		// Déplacement des astéroïdes 
		void Move();
		// Définit si l'objet est dans les limites du jeu
		bool EstDansLeJeu() const;
		// Vérifie les collisions avec les ennemis et le joueur
		bool VerifierCollision(Vaisseau* vaisseau);
	private:
		// Les 5 textures possible pour les obstacles
		static Texture t[NB_MAX_OBSTACLE];
		// La direction de l'obstacle
		Vector2f mouvement;
		// Définit si l'objet est dans les limites du jeu
		bool estDansLeJeu;
		// Retourne un direction aléatoire en X ou en Y
		float GetRandomDirection(float min, float max);
		// Définit si l'objet est destructible ou non
		bool destructible; 
	};
}


