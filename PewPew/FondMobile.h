#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <thread>
#include "Constante.h"

using namespace sf;
using namespace std;
class FondMobile
{
private:
	// Le sprite utilisé pour défiler en background
	Sprite fondEcran;
	// La texture du background
	Texture fondEcranT; 

	// La position en X et la vitesse en X
	int position;
	int vitesse;

	// Les dimensions de l'écran
	const int LARGEUR_ECRAN;
	const int HAUTEUR_ECRAN;

	//Le deuxième fond utilisé pour défiler en background
	Sprite fondEcran2;
	
public:
	// Constructeur
	FondMobile(const int vitesse);
	
	bool SetTexture(const char * path);
	// Méthode de défilement
	void Move(const int thrust);
	// Méthode d'affichage
	void Draw(RenderWindow* rw);
	// Méthodes pour augmenter ou diminuer la vitesse
	void SpeedUp();
	void SlowDown();
	// Remet la vitesse à la vitesse de départ
	void ResetSpeed();
};

