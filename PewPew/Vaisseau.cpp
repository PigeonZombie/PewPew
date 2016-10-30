#include "Vaisseau.h"
#define CENTRE 24
using namespace PewPew;

/// <summary>
/// Constructeur de la classe Vaisseau
/// </summary>
Vaisseau::Vaisseau() :image(CENTRE)
{
	estJoueur = false;
}


Vaisseau::~Vaisseau()
{
}

/// <summary>
/// Obtient le rectangle englobant le vaisseau
/// </summary>
/// <returns></returns>
IntRect Vaisseau::GetRect() const
{
	IntRect rect = IntRect(this->getGlobalBounds());
	return rect;
}
/// <summary>
/// Retourne le nombre de points de vie du vaisseau.
/// </summary>
/// <returns>Le nombre de points de vie</returns>
float Vaisseau::GetPV() const
{
	return pointsVie;
}
/// <summary>
/// Inflige des dégâts au vaisseau (diminue son nombre de PV)
/// </summary>
/// <param name="degats">La quantité de dégâts à infliger</param>
void Vaisseau::InfligerDegats(const int degats)
{
	pointsVie -= degats;
}
/// <summary>
/// Retourne la vitesse du vaisseau
/// </summary>
int Vaisseau::GetVitesse() const
{
	return this->vitesse;
}