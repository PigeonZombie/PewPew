#include "Ecran.h"

using namespace PewPew;
Ecran::Ecran()
{
}


Ecran::~Ecran()
{
}

/// <summary>
/// Charge toutes les textures, les assigne au bon Sprite et les positionne
/// </summary>
/// <returns>Vrai si les textures sont chargées, faux sinon</returns>
bool Ecran::Init()
{
	if (!tBackground1.loadFromFile("Sprites\\startBackground.jpg"))
		return false;
	if (!tBackground2.loadFromFile("Sprites\\endBackground.jpg"))
		return false;
	background.setTexture(tBackground1);
	background.setPosition(0, 0);
	activeBackground = 1;
	return true;
}
/// <summary>
/// Retourne le fond d'écran actif 
/// </summary>
/// <returns>Le sprite de fond d'écran</returns>
Sprite& Ecran::GetBackground()
{
	return background;
}
/// <summary>
/// Alterne les fond d'écran (début ou fin) 
/// </summary>
void Ecran::SwitchBackground()
{
	if (activeBackground == 1)
	{
		background.setTexture(tBackground2);
		activeBackground = 2;
	}
	else
	{
		background.setTexture(tBackground1);
		activeBackground = 1;
	}
}