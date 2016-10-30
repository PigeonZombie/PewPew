// Super-classe abstraite dont héritent le joueur et tous les ennemis
#pragma once
#include <SFML\Graphics.hpp>
#include "TirChercheur.h"
#include "TirFactory.h"
#include "IObserver.h"
#include "Soin.h"
#include "Bouclier.h"


using namespace sf;

/// <summary>
/// Classe de Vaisseau Spatial abstrait 
/// Super-classe de Joueur et Ennemi
/// </summary>
namespace PewPew
{
	class Vaisseau :public Sprite, public IObserver
	{
	public:
		// Constructeur
		Vaisseau();
		virtual ~Vaisseau();
		// Méthodes de déplacement et d'initialisation des graphiques à redéfinir
		virtual void Mouvement() = 0;
		virtual void InitGraphiques() = 0;
		//Méthode pour tirer, à redéfinir.
		virtual Tir* tirer() = 0;
		// Obtient le rectangle englobant le vaisseau
		IntRect GetRect() const;
		// Retourne le nombre de points de vie du vaisseau
		float GetPV() const;
		// Inflige des dégâts au vaisseau (diminue son nombre de PV)
		void InfligerDegats(const int degats);
		// Notification de la part des bonus
		virtual void Notify(Subject* _subject) = 0;
		virtual int GetVitesse() const;
	protected:
		// La vitesse du vaisseau
		int vitesse;
		// Le thrust du vaisseau
		int thrust;
		// Le nombre de points de vie du vaisseau
		float pointsVie;
		// Le frame d'animation
		int image;
		// Le rectangle d'animation du joueur
		IntRect rectangleAnimation;
		// Identifie le vaisseau du joueur
		bool estJoueur;
	};
}

