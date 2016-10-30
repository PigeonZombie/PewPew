#include "Tir.h"
#include "Ennemi.h"
#include "Joueur.h"

using namespace PewPew;

Tir::Tir() :
	position(new sf::Vector2f(0, 0)),
	direction(new sf::Vector2f(0, 0)),
	puissance(0),
	vitesse(0)
{
	joueur = false;
}

Tir::Tir(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance, float _vitesse, int _rotation, bool _joueur) :
	position(_position),
	direction(_direction),
	puissance(_puissance),
	vitesse(_vitesse),
	rotation(_rotation),
	joueur(_joueur),
	toDelete(true)
{

}

Tir::~Tir()
{
	
}

int Tir::Init(sf::Texture &_texture)
{
	return EXIT_FAILURE;
}

void Tir::Move()
{
	
}

/// <summary>
/// Vérifie la collision avec le vaisseau passé en paramètre et inflige les dégâts à celui-ci si une collision à lieue.
/// </summary>
/// <param name="_ship">Le vaisseau avec qui vérifier la collision.</param>
/// <returns>Retourne vrai s'il y a eu une collision, sinon retourn faux.</returns>
bool Tir::VerifierCollision(Vaisseau* _ship)
{
	try
	{
		sf::IntRect rectangleProjectile = sf::IntRect(getGlobalBounds());
		sf::IntRect rS = sf::IntRect(_ship->getGlobalBounds());
		if (rectangleProjectile.intersects(rS))
		{
			if(typeid(*_ship) == typeid(Joueur))
			{
				Joueur* j = (Joueur*)_ship;
				if (j->GetPremierBouclier() != nullptr)
				{
					if (j->GetPremierBouclier()->GetColor() == couleur)
					{
						j->GetPremierBouclier()->InfligerDegats(this->puissance);
						return true;
					}
				}
			}
			_ship->InfligerDegats(this->puissance);
			return true;
		}
	}
	catch (std::exception e)
	{
		return false;
	}
}

bool Tir::VientDuJoueur() const
{
	return joueur;
}

bool Tir::ToDelete() const
{
	return toDelete;
}