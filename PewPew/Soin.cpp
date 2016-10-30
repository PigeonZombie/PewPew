#include "Soin.h"

using namespace PewPew;
/// <summary>
/// Constructeur de la classe Soin
/// </summary>
/// <param name="position">La position du bonus</param>
Soin::Soin(Vector2f position) :Bonus(position)
{
}


Soin::~Soin()
{
}
/// <summary>
/// Place la texture dans le sprite
/// </summary>
void Soin::InitGraphiques()
{
	setTexture(tSoin);
}
/// <summary>
/// Notifie les observateurs
/// </summary>
void Soin::Action()
{
	Notify_Observers(false);
}
