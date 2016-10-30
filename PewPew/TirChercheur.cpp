#include "TirChercheur.h"
#include "Vaisseau.h"

using namespace PewPew;

TirChercheur::TirChercheur() :
	TirNormal()
{

}

TirChercheur::TirChercheur(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance, float _vitesse, int _rotation, Vaisseau* _cible, bool _joueur) :
	TirNormal(_position, _direction, _puissance, _vitesse, _rotation, _joueur),
	cible(_cible)
{
	if (!joueur)
	{
		int color = rand() % 3;
		switch (color)
		{
		case 0:
			couleur = sf::Color::Red;
			break;
		case 1:
			couleur = sf::Color::Blue;
			break;
		case 2:
			couleur.r = 31;
			couleur.g = 157;
			couleur.b = 6;
			break;
		default:
			couleur = sf::Color::Yellow;
		}
		setColor(couleur);
	}
}

TirChercheur::~TirChercheur()
{
	delete this->direction;
	this->direction = nullptr;
	delete this->position;
	this->position = nullptr;
}

int TirChercheur::Init(sf::Texture &_texture)
{
	if (&_texture == nullptr)
		return EXIT_FAILURE;

	this->setTexture(_texture);
	this->setPosition(*this->position);
	this->setRotation(this->rotation);

	if (!joueur)
	{
		float actualX = this->getPosition().x;
		float actualY = this->getPosition().y;

		//Défini un vecteur entre le tir et sa cible.
		float newDirectionX = this->cible->getPosition().x - actualX;
		float newDirectionY = this->cible->getPosition().y - actualY;

		//Normalize le vecteur entre le tir et sa cible.
		float normNewDirection = sqrt((newDirectionX * newDirectionX) + (newDirectionY + newDirectionY));
		float newUDirectionX = newDirectionX / normNewDirection;
		float newUDirectionY = newDirectionY / normNewDirection;

		//Met à jour le vecteur "officiel" de direction du tir.
		this->direction->x = newUDirectionX;
		this->direction->y = newUDirectionY;

		//Déplace le tir avec la nouvelle direction.
		float newX = actualX + this->direction->x * this->vitesse;
		float newY = actualY + this->direction->y * this->vitesse;
		this->setPosition(newX, newY);
	}
}

/// <summary>
/// Déplace le tir vers sa cible.
/// </summary>
void TirChercheur::Move()
{
	float actualX = this->getPosition().x;
	float actualY = this->getPosition().y;

	if (joueur)
	{
		

		//Défini un vecteur entre le tir et sa cible.
		float newDirectionX = this->cible->getPosition().x - actualX;
		float newDirectionY = this->cible->getPosition().y - actualY;

		//Normalize le vecteur entre le tir et sa cible.
		float normNewDirection = sqrt((newDirectionX * newDirectionX) + (newDirectionY + newDirectionY));
		float newUDirectionX = newDirectionX / normNewDirection;
		float newUDirectionY = newDirectionY / normNewDirection;

		//Met à jour le vecteur "officiel" de direction du tir.
		this->direction->x = newUDirectionX;
		this->direction->y = newUDirectionY;

		//Déplace le tir avec la nouvelle direction.
		float newX = actualX + this->direction->x * this->vitesse;
		float newY = actualY + this->direction->y * this->vitesse;
		this->setPosition(newX, newY);
	}
	else
	{
		float newX = actualX + this->direction->x * this->vitesse;
		float newY = actualY + this->direction->y * this->vitesse;
		this->setPosition(newX, newY);
	}
}

void TirChercheur::SetCible(Vaisseau* _newCible)
{
	this->cible = _newCible;
}

Vaisseau* TirChercheur::GetCible() const
{
	return this->cible;
}