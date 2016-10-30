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
		// Nombre maximum d'ennemis pouvant �tre � l'�cran en m�me temps
		static const int NBR_VAISSEAUX = 10;

		// Ecrans de d�but et de fin
		Ecran ecran;
		// Fen�tre de jeu
		RenderWindow mainWin;
		View view;
		Event event;
		// Interface utilisateur
		UI* ui;
		// Indique si la partie est termin�e 
		bool gameOver;

		// Fond d'�cran de d�filement
		FondMobile fond;
		int thrust;
		// Variables pour g�rer l'apparition des obstacles et des ennemis
		int compteurEnnemi;
		int compteurObstacle;
		int prochainVaisseau;
		int prochainObstacle;

		// Textures du vaisseau joueur et des projectiles 
		Texture shipT;
		Texture tirT;

		// Le vaisseau du joueur et son vecteur de d�placement
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

		// Appelle les m�thodes d'initialisation de chaque classe
		bool Init();
		// Enregistre les entrants du joueur
		void GetInputs();
		// Mise � jour des �l�ments principaux du jeu
		void Update();
		// Mise � jour du mouvement de tous les �l�ments
		void MovementUpdate();
		// Mise � jour des bonus
		void BonusUpdate();
		// Mise � jour des projectiles
		void ProjectileUpdate();
		// Mise � jour des obstacles
		void ObstacleUpdate();
		// Dessine le jeu 
		void Draw();
		// M�thodes pour g�n�rer un ennemi, un bonus ou un obstacle
		void GenererEnnemi();
		void GenererBonus(Ennemi* ennemi);
		void GenererObstacle();

		// Ajoute un projectile
		void AddShot(Tir* _newTir);

		// Active un bonus en v�rifiant les collisions avec le joueur
		void ActiverBonus(IntRect rect);

	public:
		// Constructeur et destructeur
		Game();
		virtual ~Game();
		// Point d'entr� de la Game
		int Run();
	};
}

