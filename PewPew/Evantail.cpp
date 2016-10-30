#define _USE_MATH_DEFINES
#include "Evantail.h"
#include <math.h>
using namespace PewPew;

Vector2f* Evantail::directions[Evantail::NB_SHOTS];

/// <summary>
/// Constructeur de la classe Evantail
/// </summary>
Evantail::Evantail()
{
	pointsVie = 3;
	vitesse = 7;
}


Evantail::~Evantail()
{
	
}
/// <summary>
/// Mouvement du vaisseau: avance vers le centre de l'écran et y reste 
/// </summary>
void Evantail::Mouvement()
{
	//Reste le plus possible au centre de l'écran 
	if (getPosition().x < LARGEUR / 2 - 30)
		move(vitesse, 0);
	else if (getPosition().x > LARGEUR/2 + 30)
		move(-vitesse, 0);
}
/// <summary>
/// Méthode de tir par défaut de la super-classe abstraite, non utilisée pour l'Evantail
/// </summary>
/// <returns></returns>
Tir* Evantail::tirer()
{
	return nullptr;
}
/// <summary>
/// Crée un nouveau projectile 
/// </summary>
/// <param name="_k">L'index du projectile</param>
/// <returns></returns>
Tir* Evantail::tirer(int _k)
{
	Vector2f* d = new Vector2f(*Evantail::directions[_k]);
	Vector2f* p = new Vector2f((this->getPosition().x + d->x * 10), ((this->getPosition().y + d->y * 10) - this->getTexture()->getSize().y / 3));
	return TirFactory::CreerTir(p, d, 1, 10);
}
/// <summary>
/// Place la texture dans le sprite et ajuste sa taille
/// </summary>
void Evantail::InitGraphiques()
{
	setTexture(tEvantail);
	setScale(0.5f, 0.5f);
	setRotation(270);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}
/// <summary>
/// Initialise les directions de chacun des projectiles tirés par le vaisseau en un coup
/// </summary>
void Evantail::InitDirections()
{
	Vector2f tVector(1, 0);
	float angleEntreRotations = 140 / NB_SHOTS;
	float rotation = 120;

	for (int i = 0; i < Evantail::NB_SHOTS; i++)
	{
		Evantail::directions[i] = Evantail::RotateVector(tVector, -rotation);
		rotation += angleEntreRotations;
	}
}
/// <summary>
/// Effectue la rotation d'un vecteur pour déterminer sa direction
/// </summary>
/// <param name="_vector">The _vector.</param>
/// <param name="_rotation">The _rotation.</param>
/// <returns>Un vecteur qui a subi une rotation</returns>
Vector2f* Evantail::RotateVector(Vector2f &_vector, float _rotation)
{
	float toRadians = _rotation * M_PI / 180;
	float cosA = cos(toRadians);
	float sinA = sin(toRadians);

	float newX = (cosA * _vector.x) - (sinA * _vector.y);
	float newY = (sinA * _vector.x) + (cosA * _vector.y);

	return new Vector2f(newX, newY);
}
