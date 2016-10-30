// Super-classe de pour tous les types d'ennemis. Hérite de Vaisseau
#pragma once
#include "Vaisseau.h"
#include <SFML\Graphics.hpp>
#include "Constante.h"
#include "BombeExplo.h"
#include "BombeMagnetique.h"
namespace PewPew
{
	class Ennemi:public Vaisseau
	{
	public:
		// Constructeur et destructeur
		Ennemi();
		virtual ~Ennemi();
		// Méthodes abstraites de mouvement et de tir (propres à chaque ennemi)
		virtual void Mouvement() = 0;
		virtual Tir* tirer() = 0;
		// Placer les textures dans les sprites (propre à chaque ennemi)
		virtual void InitGraphiques()=0;
		// Charge toutes les textures des ennemis
		static bool LoadShips();
		// Vérifie les collisions avec le joueur
		bool VerifierCollisionAvecJoueur(const IntRect rectJoueur);
		// Retourne le rectangle de collision des vaisseau (à des fins de déboguage)
		virtual RectangleShape GetCollisionBox();
		// Réagir à un signal d'un sujet
		void Notify(Subject* _subject);
		// Indique si le vaisseau peut tirer
		bool CanShoot() const;
		// Retourne la valeur en points de l'ennemi
		int GetPoints() const;
	protected:
		// Les textures des ennemis
		static Texture tBase;
		static Texture tBaseAmelioree;
		static Texture tMultishot;
		static Texture tEvantail;
		static Texture tKamikaze;
		static Texture tBoss;
		// Indique si le vaisseau peut tirer
		bool canShoot;
		// Variable pour calculer le temps d'effet de la bombe explosive
		int time;
		// Valeur en points de l'ennemi
		int valeur;
	private:
		// Obtient un nombre flottant aléatoire dans une plage
		float GetRandomDirection(float min, float max);
	};
}


