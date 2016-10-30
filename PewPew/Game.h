// Classe principale du jeu
#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "FondMobile.h"
#include "UI.h"
#include "Vaisseau.h"
#include "Joueur.h"
#include "Ennemi.h"
#include "Base.h"
#include "BaseAmelioree.h"
#include "TirChercheur.h"
#include "TirBoss.h"
#include "Constante.h"
#include "Multishot.h"
#include "Evantail.h"
#include "Kamikaze.h"
#include "EnnemiFactory.h"
#include "BonusFactory.h"
#include "Bonus.h"
#include "Soin.h"
#include "PointsBonus.h"
#include "BombeExplo.h"
#include "Obstacle.h"
#include "SoundPlayer.h"
#include "Boss.h"
#include "Ecran.h"
using namespace sf;

namespace PewPew
{
	class Game
	{
	private:
		// Nombre maximum d'ennemis pouvant être à l'écran en même temps
		static const int NBR_VAISSEAUX = 10;

		// Ecrans de début et de fin
		Ecran ecran;
		// Fenêtre de jeu
		RenderWindow mainWin;
		View view;
		Event event;
		// Interface utilisateur
		UI* ui;
		// Indique si la partie est terminée 
		bool gameOver;

		// Fond d'écran de défilement
		FondMobile fond;
		int thrust;
		// Variables pour gérer l'apparition des obstacles et des ennemis
		int compteurEnnemi;
		int compteurObstacle;
		int prochainVaisseau;
		int prochainObstacle;

		// Textures du vaisseau joueur et des projectiles 
		Texture shipT;
		Texture tirT;

		// Le vaisseau du joueur et son vecteur de déplacement
		Joueur* vaisseauJoueur;
		Vector2i mouvementJoueur;

		// Les ennemis
		Ennemi* ennemis[NBR_VAISSEAUX];
		// Le boss (Carrier)
		Boss* boss;
		// Les projectiles 
		Tir* tirs[NB_MAX_TIRS];
		// Le nombre de frame 
		int frames;
		// Indique si le joueur peut changer d'arme 
		bool canSwitch;

		// Les bonus et les obstacles
		Bonus* listeBonus[MAX_NB_BONUS];
		Obstacle* obstacles[NB_MAX_OBSTACLE];

		// 
		//bool leftClick;
		//bool rightClick;

		// Appelle les méthodes d'initialisation de chaque classe
		bool Init();
		// Enregistre les entrants du joueur
		void GetInputs();
		// Mise à jour des éléments principaux du jeu
		void Update();
		// Mise à jour du mouvement de tous les éléments
		void MovementUpdate();
		// Mise à jour des bonus
		void BonusUpdate();
		// Mise à jour des projectiles
		void ProjectileUpdate();
		// Mise à jour des obstacles
		void ObstacleUpdate();
		// Dessine le jeu 
		void Draw();
		// Méthodes pour générer un ennemi, un bonus ou un obstacle
		void GenererEnnemi();
		void GenererBonus(Ennemi* ennemi);
		void GenererObstacle();

		// Ajoute un projectile
		void AddShot(Tir* _newTir);

		// Active un bonus en vérifiant les collisions avec le joueur
		void ActiverBonus(IntRect rect);

	public:
		// Constructeur et destructeur
		Game();
		virtual ~Game();
		// Point d'entré de la Game
		int Run();
	};
}

