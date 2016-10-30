#include "PointsBonus.h"
using namespace PewPew;
/// <summary>
/// Constructeur de la classe Point Bonus
/// </summary>
/// <param name="position">La position de départ</param>
PointsBonus::PointsBonus(Vector2f position) :Bonus(position)
{
	// Le point bonus a une valeur choisie au hasarf entre 10 et 59
	value = (rand() % 50)+10;
}


PointsBonus::~PointsBonus()
{
}
/// <summary>
/// Place la texture dans le sprite
/// </summary>
void PointsBonus::InitGraphiques()
{
	setTexture(tPoints);
}
/// <summary>
/// Notifie les observateurs 
/// </summary>
void PointsBonus::Action()
{
	Notify_Observers(false);
}
/// <summary>
/// Obtient la valeur du bonus
/// </summary>
/// <returns>la valeur du bonus</returns>
int PointsBonus::GetValeur() const
{
	return value;
}