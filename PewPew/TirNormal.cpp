#include "TirNormal.h"

using namespace PewPew;

TirNormal::TirNormal() :
	Tir()
{

}

TirNormal::TirNormal(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance, float _vitesse, int _rotation, bool _joueur) :
	Tir(_position, _direction, _puissance, _vitesse, _rotation, _joueur)
{
	//Si le tir de vient pas du joueur,
	if (!joueur)
	{
		//lui donné une couleur aléatoire entre bleu, rouge ou vert.
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

/// <summary>
/// Delete le vecteur de position et de direction.
/// </summary>
TirNormal::~TirNormal()
{
	delete this->direction;
	this->direction = nullptr;
	delete this->position;
	this->position = nullptr;
}

/// <summary>
/// Initialise la texture, la position et la rotation du tir.
/// </summary>
/// <param name="_texture">La texture à utiliser.</param>
/// <returns>Retourne EXIT_FAILURE si la texture est NULL, sinon retourne EXIT_SUCCESS.</returns>
int TirNormal::Init(sf::Texture &_texture)
{
 	if (&_texture == nullptr)
		return EXIT_FAILURE;

	this->setTexture(_texture);
	this->setPosition(*this->position);
	this->setRotation(this->rotation);
	return EXIT_SUCCESS;
}

/// <summary>
/// Déplace le tir en fonction du vecteur de direction.
/// </summary>
void TirNormal::Move()
{
	float actualX = this->getPosition().x;
	float actualY = this->getPosition().y;

	float newX = actualX + this->direction->x * this->vitesse;
	float newY = actualY + this->direction->y * this->vitesse;

	this->setPosition(newX, newY);
}