#include "BombeExplo.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe BombeExplo
/// </summary>
/// <param name="position">La position de la bombe</param>
BombeExplo::BombeExplo(Vector2f position) :Bonus(position) 
{
	animation = 0;
}


BombeExplo::~BombeExplo()
{
}

/// <summary>
/// Place la texture dans le sprite , choisi une couleur au hasard et positionne la bombe
/// </summary>
void BombeExplo::InitGraphiques()
{
	setTexture(tBombeExplosive);
	int color = rand() % 3;
	// Choix d'une couleur au hasard
	switch (color)
	{
	case 0:
		couleur = Color::Red;
		break;
	case 1:
		couleur = Color::Blue;
		break;
	case 2:
		couleur.r = 31;
		couleur.g = 157;
		couleur.b = 6;
		break;
	default:
		couleur = Color::Yellow;
	}
	setColor(couleur);
	size = Vector2f(tBombeExplosive.getSize().x / 13, tBombeExplosive.getSize().y);
	step = size.x;
	// Rectangle d'animation
	cadreBombe.left = 0;
	cadreBombe.top = 0;
	cadreBombe.width = size.x;
	cadreBombe.height = size.y;
	setTextureRect(cadreBombe);
}
/// <summary>
/// Gère l'animation de la bombe et avise ses observateurs lors de l'explosion
/// </summary>
void BombeExplo::Action()
{
	if (animation == 70 && actif)
		Notify_Observers(false);
	if (actif && animation < ANIMATION_MAXIMALE)
	{
		if (animation < 70)
			animation++;
		animation++;
		if (animation % 10 == 0)
		{
			cadreBombe.left += step;
			setTextureRect(cadreBombe);
		}
	}
	if (animation == 120)
		termine = true;
}
/// <summary>
/// Retourne la couleur de la bombe
/// </summary>
/// <returns>Bleu, Rouge ou Vert(couleur personnalisée)</returns>
Color BombeExplo::GetColor() const
{
	return couleur;
}