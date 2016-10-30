// Fabrique statique de bonus et d'armes
#pragma once
#include "Bonus.h"
#include "Soin.h"
#include "Bouclier.h"
#include "PointsBonus.h"
#include "Multiplicateur.h"
#include "BombeExplo.h"
#include "BombeMagnetique.h"
#include "ArmeCharge.h"
namespace PewPew
{
	class BonusFactory
	{
	public:		
		/// <summary>
		/// Crée le nouveau bonus ou la nouvelle arme
		/// </summary>
		/// <param name="random">Le bonus à générer</param>
		/// <param name="position">La position de départ du bonus</param>
		/// <returns>Le nouveau bonus ou arme</returns>
		static Bonus* CreerBonus(int random, Vector2f position)
		{
			if (random >=0  && random <4)
			{
				return new Soin(position);
			}
			else if (random >=4 && random <15)
			{
				return new Bouclier(position);
			}
			else if (random>=15 && random<16)
			{ 
				return new PointsBonus(position);
			}
			else if (random >=16 && random <19)
			{
				return new Multiplicateur(position);
			}
			else if (random >=19 && random <22)
			{
				return new BombeExplo(position);
			}
			else if (random >= 22 && random < 26)
			{
				return new BombeMagnetique(position);
			}
			else if (random >= 26 && random < 30)
			{
				return new ArmeNormalPlus(1, 10, 30, position, false);
			}
			else if (random >= 30 && random < 35)
			{
				return new ArmeTriangle(1, 10, 30, position, false, 3);
			}
			else if (random >= 30 && random < 35)
			{
				return new ArmeCharge(3, 30, 5, position, false);
			}
			else if (random >= 35 && random < 40)
				return nullptr;
		}
	private:
		// Empêcher d'instancier la classe 
		BonusFactory();
	};
}