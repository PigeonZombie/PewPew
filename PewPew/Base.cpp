#include "Base.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe du vaisseau de Base
/// </summary>
Base::Base()
{
	pointsVie = 1;
	vitesse = 6;
}


Base::~Base()
{
}
/// <summary>
/// Le vaisseau se déplace en ligne droite de droite à gauche 
/// </summary>
void Base::Mouvement()
{
	move(-vitesse, 0);
}
/// <summary>
/// Méthode de tir: le vaisseau de base tire directement devant lui
/// </summary>
/// <returns>Un nouveau projectile</returns>
Tir* Base::tirer()
{
	return TirFactory::CreerTir(new Vector2f(this->getPosition().x, (this->getPosition().y - (this->getGlobalBounds().height / 2))), new Vector2f(-1, 0), 1, 10);
}
/// <summary>
/// Place la texture dans le sprite et ajuste sa taille 
/// </summary>
void Base::InitGraphiques()
{
	setTexture(tBase);
	setScale(0.5f, 0.5f);
	setRotation(270);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}
