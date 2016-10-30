#define _USE_MATH_DEFINES
#include "TirEvantail.h"
#include <math.h>
#include "Ennemi.h"
#include "Joueur.h"

using namespace PewPew;
using namespace sf;

TirEvantail::TirEvantail()
{

}

TirEvantail::TirEvantail(sf::Vector2f* _position, int _nbTirs, int _puissance, float _vitesse, int _rotation, bool _joueur) :
	Tir(_position, nullptr, _puissance, _vitesse, _rotation, _joueur),
	nbTirs(_nbTirs)
{
	this->toDelete = false;
}

TirEvantail::~TirEvantail()
{
	//Delete chacun des tires.
	for (int i = 0; i < this->tirs.GetSize(); i++)
		if (this->tirs[i].GetContent() != nullptr)
			delete this->tirs[i].GetContent();

	//delete la position.
	if (this->position != nullptr)
	{
		delete this->position;
		this->position = nullptr;
	}
}

/// <summary>
/// Initialise les tires et les angles.
/// </summary>
/// <param name="_texture">Texture à utiliser pour les tires.</param>
/// <returns>Retourne EXIT_FAILURE si la texture est null, sinon retourne EXIT_SUCCESS</returns>
int TirEvantail::Init(sf::Texture &_texture)
{
	if (&_texture == nullptr)
		return EXIT_FAILURE;

	//Initialiee les angles.
	InitAngles();
	//Crée un tir par angle et l'ajoute à la liste des tires.
	for (int i = 0; i < nbTirs; i++)
	{
		Vector2f* _pos = new Vector2f((this->position->x + (this->angles[i].GetContent()->x * 10)), (this->position->y + (this->angles[i].GetContent()->y * 10)));
		this->tirs.Add(new TirNormal(_pos, this->angles[i].GetContent(), 1, 7, 0, this->joueur));
	}

	//Initialiee chacun des tires créés.
	for (int i = 0; i < nbTirs; i++)
	{
		this->tirs[i].GetContent()->Init(_texture);
	}

	return EXIT_SUCCESS;
}

/// <summary>
/// Initializes the angles.
/// </summary>
void TirEvantail::InitAngles()
{
	//Défini un vecteur d'une longueur de 1 en 'x' et 0 en 'y'.
	Vector2f tVector(1, 0);
	float angleEntreRotations = 0;
	float rotation = 0;

	if (this->joueur)
	{
		//Défini l'angle entre chaque tirs.
		angleEntreRotations = -140 / nbTirs;
		//Définie le premier angle.
		rotation = 46;
	}
	else
	{
		angleEntreRotations = 140 / nbTirs;
		rotation = 120;
	}

	for (int i = 0; i < nbTirs; i++)
	{
		//ajouter l'angle à la liste.
		//L'angle est le vecteur défini plus haut sur lequel une rotation de l'angle voulue est effecté.
		angles.Add(this->RotateVector(tVector, rotation));
		//puis augmanter l'angle du nombre de degrée entre chaque angle.
		rotation += angleEntreRotations;
	}
}

/// <summary>
/// Effectu une rotation du nombre de degrée passés en paramètre sur le vecteur passé en paramètre.
/// </summary>
/// <param name="_vector">Le vecteur qui va recevoir la rotation.</param>
/// <param name="_rotation">Nombre de degrée.</param>
/// <returns>Retourn un pointeur vers le nouveau vecteur créé à la suite de la rotation.</returns>
Vector2f* TirEvantail::RotateVector(Vector2f &_vector, float _rotation)
{
	//Transforme les degrées en radians.
	float toRadians = _rotation * M_PI / 180;
	//Calcul le cos et le sin de l'angle.
	float cosA = cos(toRadians);
	float sinA = sin(toRadians);

	//Calcul le nouveau 'x' et 'y' à l'aide de la matrice de rotation.
	float newX = (cosA * _vector.x) - (sinA * _vector.y);
	float newY = (sinA * _vector.x) + (cosA * _vector.y);

	//Retourne le nouveau vecteur ainsi créé.
	return new Vector2f(newX, newY);
}

void TirEvantail::Move()
{
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		this->tirs[i].GetContent()->Move();
	}
}

/// <summary>
/// Verifie la collision de chacun des tires individuellement, donc si un touche, les autres ne sont pas delete.
/// </summary>
/// <param name="_ship">Vaisseau avec lequel vérifier la collision.</param>
/// <returns>Retourne vrai s'il y a une au moins une collision, sinon retourne faux.</returns>
bool TirEvantail::VerifierCollision(Vaisseau* _ship)
{
	try
	{
		bool toucher = false;
		sf::IntRect rS = sf::IntRect(_ship->getGlobalBounds());
		//Pour chaque tirs, 
		for (int i = 0; i < this->tirs.GetSize(); i++)
		{
			sf::IntRect rectangleProjectile = sf::IntRect(this->tirs[i].GetContent()->getGlobalBounds());
			//si il y a collision,
			if (rectangleProjectile.intersects(rS))
			{
				//Infliger les dégâts,
				_ship->InfligerDegats(this->puissance);
				//delete le tir qui a touché,
				delete this->tirs[i].GetContent();
				//l'enlever de la liste,
				this->tirs.Remove(i);
				//indiquer qu'il y a eu au moins une collision.
				toucher = true;
			}
		}

		//s'il ne reste plus de tirs dan la liste, indiquer que le tire peut être retiré de la liste de tirs dans la class Game.
		if (this->tirs.GetSize() == 0)
			toDelete = true;

		//Retourner s'il y a eu une collision.
		return toucher;
	}
	catch (std::exception e)
	{
		return false;
	}
}

void TirEvantail::Draw(sf::RenderWindow &_window)
{
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		_window.draw(*this->tirs[i].GetContent());
	}
}