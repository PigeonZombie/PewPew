#define _USE_MATH_DEFINES
#include "Kamikaze.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe Kamikaze
/// </summary>
Kamikaze::Kamikaze()
{
	pointsVie = 2;
	vitesse = 6;
}


Kamikaze::~Kamikaze()
{

}
/// <summary>
/// Mouvement du Kamikaze: fonce vers le joueur
/// </summary>
/// <param name="target">La position du joueur</param>
void Kamikaze::Mouvement(Vector2f target)
{
	//S'il se retrouve derrière le joueur, le vaisseau arrête de le suivre
	float angle = atanf((target.y - getPosition().y) / (target.x - getPosition().x));
	if (target.x < getPosition().x)
	{
		angle += M_PI;
	}
	if (target.x > getPosition().x)
	{
		move(-vitesse, 0);
	}
	else
		move((cos(angle) * vitesse), (sin(angle) * vitesse));
}
/// <summary>
/// Mouvement par défaut (non utilisé)
/// </summary>
void Kamikaze::Mouvement()
{
	move(-vitesse, 0);
}
/// <summary>
/// Tir par défaut (non utilisé, le Kamikaze ne tire pas)
/// </summary>
/// <returns>nullptr</returns>
Tir* Kamikaze::tirer()
{
	return nullptr;
}
/// <summary>
/// Place la texture dans le sprite et ajuste sa taille
/// </summary>
void Kamikaze::InitGraphiques()
{
	setTexture(tKamikaze);

	setScale(0.5f, 0.5f);
	setRotation(270);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}
