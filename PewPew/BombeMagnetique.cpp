#include "BombeMagnetique.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe BombeMagnetique
/// </summary>
/// <param name="position">La position de la bombe</param>
BombeMagnetique::BombeMagnetique(Vector2f position) :Bonus(position)
{
	animation = 0;
	
}


BombeMagnetique::~BombeMagnetique()
{
}
/// <summary>
/// Place la texture dans le sprite et positionne la bombe
/// </summary>
void BombeMagnetique::InitGraphiques()
{
	setTexture(tBombeElectro);

	size = Vector2f(tBombeExplosive.getSize().x / 13, tBombeExplosive.getSize().y);
	step = size.x;
	cadreBombe.left = 0;
	cadreBombe.top = 0;
	cadreBombe.width = size.x;
	cadreBombe.height = size.y;
	setTextureRect(cadreBombe);
}
/// <summary>
/// Gère l'animation de la bombe et avise ses observateurs lors de l'explosion
/// </summary>
void BombeMagnetique::Action()
{
	if (animation == 120)
	{
		setTextureRect(IntRect(-20, -20, 10, 10));
	}
	if (animation >= 70 && actif)
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
}