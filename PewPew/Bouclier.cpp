#include "Bouclier.h"

using namespace PewPew;
/// <summary>
/// Constructeur de la classe 
/// </summary>
/// <param name="position">La position de départ de la texture</param>
Bouclier::Bouclier(Vector2f position) :Bonus(position)
{
	pointsVie = (rand() % 4) + 1;
}


Bouclier::~Bouclier()
{
}
/// <summary>
/// Place la texture dans le sprite et choisi au hasard une couleur pour le bouclier
/// </summary>
void Bouclier::InitGraphiques()
{
	// Assignation de la texture
	setTexture(tBouclier);
	// Choix de la couleur au hasard
	int _color = rand() % 3;
	switch (_color)
	{
	case 0:
		color = Color::Red;
		break;
	case 1:
		color = Color::Blue;
		break;
	case 2: 
		color.r = 31;
		color.g = 157;
		color.b = 6;
		break;
	default:
		color = Color::Yellow;
	}
	// Construction du cercle représentant le bouclier activé
	shape.setFillColor(Color::Transparent);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(2);
	shape.setRadius(RAYON_BOUCLIER);
}
/// <summary>
/// Active le bouclier et notifie les observateurs
/// </summary>
void Bouclier::Action()
{
	if (pointsVie > 0)
		Notify_Observers(false);
	else
		termine = true;
}
/// <summary>
/// Gets the color.
/// </summary>
Color Bouclier::GetColor() const
{
	return color;
}
/// <summary>
/// Gets the shape of the shield.
/// </summary>
CircleShape Bouclier::GetShape() const
{
	return shape;
}
/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void Bouclier::SetPosition(const Vector2f position)
{
	shape.setPosition(position);
}
/// <summary>
/// Gets the remaining health.
/// </summary>
/// <returns></returns>
int Bouclier::GetPV() const
{
	return pointsVie;
}
/// <summary>
/// Enlève des points de vie au bouclier
/// </summary>
/// <param name="degats">Les dégats à infliger</param>
void Bouclier::InfligerDegats(int degats)
{
	pointsVie -= degats;
}