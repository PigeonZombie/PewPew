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
		// Liste d'armes sp�ciales 
		myns::List<Arme> armes;
		// Indique si le joueur est en train de charger son tir
		bool isCharging;
		// Constructeur
		Joueur();
	public:
		// Mouvement par d�faut
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
		// Lib�re l'instance du joueur
		void Release();
		// Obtient la bo�te de collision � des fins de d�boguage
		RectangleShape GetCollisionBox();
		// R�agir � une notification d'objet
		void Notify(Subject* _subject);
		// Retourne le bouclier sur le dessus de la pile
		Bouclier* GetPremierBouclier() const;
		// Retire le bouclier sur le dessus de la pile
		void EnleverBouclier();
		// Ajoute une arme sp�ciale � la liste
		void AjouterArme(Arme* _arme);
		// M�thode de tir
		Tir* tirer();
		void UpdateCadences();
		//Active l'arme qui suit celle activer dans la liste.
		//Si c'est la derni�re de la liste qui est activer, active la premi�re.
		//Retourne vrai si un chagement � eu lieu.
		bool ChangerArme();		
		// V�rifie que l'arme a encore des munitions
		void VerifierMunitions(int _index);

		// Ajouter des points au score du joueur
		static void AjouterScore(const int points);
		// Obtient le score
		static int GetScore();
		// Obtient le multiplicateur 
		static int GetMultiplicateur();
		// Enl�ve un multiplicateur
		static void EnleverMultiplicateur();

		// Change la valeur de isCharging
		void SetIsCharging(bool _value);
	};
}


