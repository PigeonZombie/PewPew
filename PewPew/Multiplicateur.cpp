#include "Multiplicateur.h"
using namespace PewPew;
/// <summary>
/// Constructeur de la classe Multiplicateur
/// </summary>
/// <param name="position">La position de départ</param>
Multiplicateur::Multiplicateur(Vector2f position) :Bonus(position)
{
	frameDuration = (60) * 6;
	frames = 0;
}


Multiplicateur::~Multiplicateur()
{
}
/// <summary>
/// Place la texture dans le sprite
/// </summary>
void Multiplicateur::InitGraphiques()
{
	setTexture(tMultiplier);
}
/// <summary>
/// Notifie les observeurs et termine le multiplicateur après un certain temps
/// </summary>
void Multiplicateur::Action()
{
	frames++;
	if (frames >= frameDuration)
		termine = true;

	Notify_Observers(false);
}
