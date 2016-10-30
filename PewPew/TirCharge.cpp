#include "TirCharge.h"
#include "Joueur.h"

using namespace PewPew;

TirCharge::TirCharge(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance, float _vitesse, int _rotation, bool _joueur) : 
	Tir(_position, _direction, _puissance, _vitesse, _rotation, _joueur),
	isShot(false)
{

}

TirCharge::~TirCharge()
{
	if (this->position != nullptr)
		delete this->position;

	if (this->direction != nullptr)
		delete this->direction;
}

int TirCharge::Init(sf::Texture &_texture)
{
	if (&_texture == nullptr)
		return EXIT_FAILURE;

	this->setTexture(_texture);
	this->setPosition(*this->position);
	this->setRotation(this->rotation);
}

void TirCharge::Move()
{
	float actualX = this->getPosition().x;
	float actualY = this->getPosition().y;

	float newX = actualX + this->direction->x * this->vitesse;
	float newY = actualY + this->direction->y * this->vitesse;

	this->setPosition(newX, newY);
}

/// <summary>
/// Déplace le tir avec le vaisseau passer en paramètre si le tir est encore en train d'être charger,
/// sinon, déplace le tir comme un TirNormal.
/// </summary>
/// <param name="_vaisseau">Vaisseau qui effectu le tir.</param>
/// <returns>Retourne vrai si le tir est tiré (s'il n'est plus en charge), sinon retourne faux.</returns>
bool TirCharge::Move(Vaisseau* _vaisseau)
{
	if (!isShot)
	{
		this->setPosition((_vaisseau->getPosition().x - (this->getTexture()->getSize().x / 2)), (_vaisseau->getPosition().y - (this->getTexture()->getSize().y / 2)));
		this->UpdateCharge();
		if (this->charge >= this->CHARGE_MAX)
			this->isShot = true;

		if (this->isShot)
			return true;
		else
			return false;
	}
	else
	{
		this->Move();
		return true;
	}
}

bool TirCharge::VerifierCollision(Vaisseau* _ship)
{
	if (!isShot)
		return false;

	try
	{
		sf::IntRect rectangleProjectile = sf::IntRect(getGlobalBounds());
		sf::IntRect rS = sf::IntRect(_ship->getGlobalBounds());
		if (rectangleProjectile.intersects(rS))
		{
			if (typeid(*_ship) == typeid(Joueur))
			{
				Joueur* j = (Joueur*)_ship;
				if (j->GetPremierBouclier() != nullptr)
				{
					if (j->GetPremierBouclier()->GetColor() != couleur)
					{
						j->GetPremierBouclier()->InfligerDegats(this->puissance);
						return true;
					}
				}
			}
			else
				_ship->InfligerDegats(this->puissance);
			return true;
		}
	}
	catch (std::exception e)
	{
		return false;
	}
}

/// <summary>
/// Augmente la taille et la puissance du tir.
/// </summary>
void TirCharge::UpdateCharge()
{
	this->charge += 1;
	this->puissance = (this->charge / 30);
	float scale = (float)this->charge / 10;
  	this->setScale(scale, scale);
}

/// <summary>
/// Indique que le propriétaire du tir a tiré.
/// </summary>
void TirCharge::Shoot()
{
	this->isShot = true;
}

bool TirCharge::IsShot() const
{
	return this->isShot;
}

int TirCharge::GetCharge() const
{
	return this->charge;
}