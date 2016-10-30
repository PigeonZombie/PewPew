// Classe qui gère l'interface Utilisateur
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Constante.h"
#include "IObserver.h"
#include "Bouclier.h"
#include "Multiplicateur.h"
#include "PointsBonus.h"
#include "ArmeCharge.h"
#include "ArmeNormal.h"
#include "ArmeNormalPlus.h"
#include "ArmeTriangle.h"

using namespace sf;

namespace PewPew
{
	static class UI:public IObserver
	{
	public:
		// Constructeur
		UI();
		// Modifie le texte qui affiche les vies du joueur
		static void SetVies(int vies);
		// Modifie le texte qui affiche les points du joueur
		static void SetPoints(int points);
		// Modifie le texte qui affiche les points de vie du bouclier
		static void SetBouclier(int points);
		// Réinitialise le texte qui affiche le bouclier courant du joueur
		static void ResetBouclier();
		// Charge tous les éléments (font, texture) 
		static bool InitGraphiques();
		// Affiche le score du joueur à la fin de la partie
		static void AfficherScore(RenderWindow* rw);
		// Dessine tous les éléments de l'interface
		static void Draw(RenderWindow* rw);
		// Méthode de l'observeur
		void Notify(Subject* _subject);

		
	private: 
		// La police pour tous les textes de l'interface
		static Font font;
		// Le texte qui affiche les vies, son board et sa texture 
		static Text vie;
		static Sprite uiVie;
		static Texture tVie;
		// Le texte qui affiche les points,son board et sa texture 
		static Text points;
		static Sprite uiPoint;
		static Texture tPoint;
		// Le texte qui affiche le multiplicateur,son board et sa texture  
		static Text multiplicateur;
		static Sprite uiMulti;
		static Texture tMulti;
		// Le texte qui affiche le bouclier courant,son board et sa texture 
		static Text bouclier;
		static Sprite uiBouclier;
		static Texture tBouclier;
		// Le texte qui affiche l'arme active et les munitions restantes, son board et sa texture 
		static Text arme;
		static Sprite uiArmeActive;
		static Texture tArme;
		static Sprite sArmeActive;

		// Les variables qui gardent en mémoire le score et le multiplicateur du joueur,
		static int score;
		static int multi;
		// Variable qui garde en mémoire les points de vie du bouclier
		static int pointBouclier;
	};
}
