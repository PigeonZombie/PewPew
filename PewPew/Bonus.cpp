#include "Bonus.h"

using namespace PewPew;

Texture Bonus::tSoin;
Texture Bonus::tBouclier;
Texture Bonus::tPoints;
Texture Bonus::tMultiplier;
Texture Bonus::tBombeExplosive;
Texture Bonus::tBombeElectro;
Texture Bonus::tArmeNormal;
Texture Bonus::tArmeNormalPlus;
Texture Bonus::tArmeTriangle;
Texture Bonus::tArmeCharge;

/// <summary>
/// Constructeur de la classe bonue
/// </summary>
/// <param name="position">La position de départ</param>
/// <param name="_isArme">Indique si le bonus est une arme spéciale ou non</param>
Bonus::Bonus(Vector2f position, bool _isArme) : actif(false), isArme(_isArme)
{
	setPosition(position);
	termine = false;
	collected = false;
}


Bonus::~Bonus()
{
}
/// <summary>
/// Charge les textures de tous les bonus 
/// </summary>
/// <returns></returns>
bool Bonus::LoadAllTextures()
{
	if (!tSoin.loadFromFile("Sprites\\soin.png"))
		return false;
	if (!tBouclier.loadFromFile("Sprites\\bouclier.png"))
		return false;
	if (!tPoints.loadFromFile("Sprites\\points.png"))
		return false;
	if (!tMultiplier.loadFromFile("Sprites\\multiplicateur.png"))
		return false;
	if (!tBombeExplosive.loadFromFile("Sprites\\Bomb.png"))
		return false;
	if (!tBombeElectro.loadFromFile("Sprites\\magnet.png"))
		return false;
	if (!tArmeNormal.loadFromFile("Sprites\\armenormal.png"))
		return false;
	if (!tArmeNormalPlus.loadFromFile("Sprites\\armenormalplus.png"))
		return false;
	if (!tArmeTriangle.loadFromFile("Sprites\\armetriangle.png"))
		return false;
	if (!tArmeCharge.loadFromFile("Sprites\\armechargee.png"))
		return false;
	return true;
}
/// <summary>
/// Vérifie s'il y a une collision entre le bonus et le joueur
/// </summary>
/// <param name="rectangleJoueur">Le rectangle englobant le joueur</param>
/// <returns>Vrai s'il y a une collision, faux sinon</returns>
bool Bonus::TesterContact(IntRect rectangleJoueur)
{
	if (IntRect(getGlobalBounds()).intersects(rectangleJoueur))
	{
		return true;
	}
	return false;
}
/// <summary>
/// Indique si le bonus est terminé, dans quel cas il doit être supprimé
/// </summary>
/// <returns></returns>
bool Bonus::EstTermine() const
{
	return termine;
}
/// <summary>
/// Active le bonus
/// </summary>
void Bonus::Activer()
{
	actif = true;
}
/// <summary>
/// Desactive le bonus 
/// </summary>
void Bonus::Desactiver()
{
	actif = false;
}
/// <summary>
/// Indique si le bonus est actif
/// </summary>
/// <returns></returns>
bool Bonus::Actif() const
{
	return actif;
}
/// <summary>
/// Termine le bonus
/// </summary>
void Bonus::Terminer()
{
	termine = true;
}
/// <summary>
/// Indique si le bonus a été ramassé par le joueur 
/// </summary>
/// <returns>Vrai si le bonus est ramassé, faux sinon</returns>
bool Bonus::Collected() const
{
	return collected;
}
/// <summary>
/// Ramasse le bonus
/// </summary>
void Bonus::Collect()
{
	if (!collected)
		collected = true;
	else
		collected = false;
}
/// <summary>
/// Determines whether this instance is a weapon
/// </summary>
/// <returns>Vrai si c'est une arme, faux sinon</returns>
bool Bonus::IsArme() const
{
	return this->isArme;
}
/// <summary>
/// Retourne la texture de l'arme de base
/// </summary>
Texture* Bonus::GetTArmeNormal()
{
	return &Bonus::tArmeNormal;
}
/// <summary>
/// Retourne la texture de l'arme Plus (tir chercheur)
/// </summary>
Texture* Bonus::GetTArmeNormalPlus()
{
	return &Bonus::tArmeNormalPlus;
}
/// <summary>
/// Retourne la texture de l'arme triangle
/// </summary>
Texture* Bonus::GetTArmeTriangle()
{
	return &Bonus::tArmeTriangle;
}
/// <summary>
/// Retourne la texture de l'arme charge
/// </summary>
Texture* Bonus::GetTArmeCharge()
{
	return &Bonus::tArmeCharge;
}