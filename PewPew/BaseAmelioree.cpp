#define _USE_MATH_DEFINES
#include "BaseAmelioree.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe BaseAmelioree
/// </summary>
BaseAmelioree::BaseAmelioree()
{
	pointsVie = 1;
	vitesse = 7;
}


BaseAmelioree::~BaseAmelioree()
{
}
/// <summary>
/// Mouvement du vaisseau amélioré: en ligne droite de droite à gauche 
/// </summary>
/// <param name="target">The target.</param>
void BaseAmelioree::Mouvement(Vector2f target)
{
	move(-vitesse, 0);
}
/// <summary>
/// Tir du vaisseau améliorée: en direction du joueur 
/// </summary>
/// <returns>Un nouveau projectile</returns>
Tir* BaseAmelioree::tirer()
{
	return TirFactory::CreerTir(new Vector2f(this->getPosition().x, (this->getPosition().y - (this->getGlobalBounds().height / 2))), new Vector2f(-1, 0), 1, 10, 0, nullptr, 1);
}
/// <summary>
/// Place la texture dans le sprite et ajuste sa taille
/// </summary>
void BaseAmelioree::InitGraphiques()
{
	setTexture(tBaseAmelioree);
	setScale(0.5f, 0.5f);
	setRotation(270);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}

