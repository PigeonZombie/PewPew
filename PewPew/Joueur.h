#pragma once
#include "Vaisseau.h"
#include "Pile.h"
#include "List.h"
#include "PointsBonus.h"
#include "Multiplicateur.h"
#include "BombeExplo.h"
#include "BombeMagnetique.h"
#include "ArmeNormal.h"
#include "ArmeNormalPlus.h"
#include "ArmeTriangle.h"
#include "ArmeCharge.h"

namespace PewPew
{
	class Joueur :public Vaisseau
	{
	private:
		// Unique instance de Joueur
		static Joueur* instance;
		// Score du joueur
		static int score;
		// Multiplicateur de points
		static int multiplicateur;
		// Pile de boucliers
		myns::Pile<Bouclier> boucliers;
		// Liste d'armes spéciales 
		myns::List<Arme> armes;
		// Indique si le joueur est en train de charger son tir
		bool isCharging;
		// Constructeur
		Joueur();
	public:
		// Mouvement par défaut
		virtual void Mouvement();
		// Mouvement du joueur
		virtual void MouvementJoueur(Vector2i& mouvement);
		// Ajuster l'animation du vaisseau
		void Monter();
		void Descendre();
		void Centrer();
		// Initialise le rectangle d'animation
		virtual void InitGraphiques();
		// Retourne l'instance de joueur
		static Joueur* GetInstance();
		// Libère l'instance du joueur
		void Release();
		// Obtient la boîte de collision à des fins de déboguage
		RectangleShape GetCollisionBox();
		// Réagir à une notification d'objet
		void Notify(Subject* _subject);
		// Retourne le bouclier sur le dessus de la pile
		Bouclier* GetPremierBouclier() const;
		// Retire le bouclier sur le dessus de la pile
		void EnleverBouclier();
		// Ajoute une arme spéciale à la liste
		void AjouterArme(Arme* _arme);
		// Méthode de tir
		Tir* tirer();
		void UpdateCadences();
		//Active l'arme qui suit celle activer dans la liste.
		//Si c'est la dernière de la liste qui est activer, active la première.
		//Retourne vrai si un chagement à eu lieu.
		bool ChangerArme();		
		// Vérifie que l'arme a encore des munitions
		void VerifierMunitions(int _index);

		// Ajouter des points au score du joueur
		static void AjouterScore(const int points);
		// Obtient le score
		static int GetScore();
		// Obtient le multiplicateur 
		static int GetMultiplicateur();
		// Enlève un multiplicateur
		static void EnleverMultiplicateur();

		// Change la valeur de isCharging
		void SetIsCharging(bool _value);
	};
}


