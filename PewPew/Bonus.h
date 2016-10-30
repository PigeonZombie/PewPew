// Super-classe des bonus (bombes, bombes magn�tiques, soins, points bonus, multiplicateurs, boucliers, armes sp�ciales)
#pragma once
#include <SFML\Graphics.hpp>
#include "Subject.h"
#include "Constante.h"
using namespace sf;

namespace PewPew
{
	class Bonus:public Sprite,public Subject
	{
	public:
		// Constructeur et destructeur 
		Bonus(Vector2f position, bool _isArme = false);
		virtual ~Bonus();
		// M�thode abstraite qui place la texture dans le sprite
		virtual void InitGraphiques() = 0;
		// Charge toutes les textures des bonus et armes 
		static bool LoadAllTextures();
		// V�rifier les collisions avec le vaisseau du joueur
		bool TesterContact(IntRect rectangleJoueur);
		// M�thode abstraite d�clenche l'effet sp�cifique au bonus
		virtual void Action() = 0;
		// Active le bonus 
		void Activer();
		// D�sactive le bonus
		void Desactiver();
		// Indique si le bonus doit �tre effac�
		bool EstTermine() const;
		// Termine le bonus
		void Terminer();
		// Indique si le bonus est actif
		bool Actif() const;
		// Indique si le bonus a �t� ramass� par le joueur 
		bool Collected() const;
		// Ramasse le bonus
		void Collect();
		// Indique si le bonus est une arme sp�ciale ou non
		bool IsArme() const;

		// Retourne les textures des armes
		static Texture* GetTArmeNormal();
		static Texture* GetTArmeNormalPlus();
		static Texture* GetTArmeTriangle();
		static Texture* GetTArmeCharge();
	protected:
		// Les textures de chaque bonus
		static Texture tBouclier;
		static Texture tSoin;
		static Texture tChargeShot;
		static Texture tTripleTir;
		static Texture tTireChercheur;
		static Texture tBombeExplosive;
		static Texture tBombeElectro;
		static Texture tMultiplier;
		static Texture tPoints;
		static Texture tArmeNormal;
		static Texture tArmeNormalPlus;
		static Texture tArmeTriangle;
		static Texture tArmeCharge;
		// Indique si le bonus est actif
		bool actif;
		// Indique si le bonus doit �tre effac�
		bool termine;
		// Indique si le bonus est ramass�
		bool collected;
		// Indique si le bonus est une arme sp�ciale
		bool isArme;
	};
}


