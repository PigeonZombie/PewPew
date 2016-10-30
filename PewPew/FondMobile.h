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
	// Le sprite utilis� pour d�filer en background
	Sprite fondEcran;
	// La texture du background
	Texture fondEcranT; 

	// La position en X et la vitesse en X
	int position;
	int vitesse;

	// Les dimensions de l'�cran
	const int LARGEUR_ECRAN;
	const int HAUTEUR_ECRAN;

	//Le deuxi�me fond utilis� pour d�filer en background
	Sprite fondEcran2;
	
public:
	// Constructeur
	FondMobile(const int vitesse);
	
	bool SetTexture(const char * path);
	// M�thode de d�filement
	void Move(const int thrust);
	// M�thode d'affichage
	void Draw(RenderWindow* rw);
	// M�thodes pour augmenter ou diminuer la vitesse
	void SpeedUp();
	void SlowDown();
	// Remet la vitesse � la vitesse de d�part
	void ResetSpeed();
};

