#pragma once
#include "Base.h"
#include "BaseAmelioree.h"
#include "Multishot.h"
#include "Evantail.h"
#include "Kamikaze.h"
#include "Constante.h"
/// <summary>
/// Fabrique statique d'Ennemis
/// </summary>
namespace PewPew
{
	class EnnemiFactory
	{
	public:		
		/// <summary>
		/// Cr�e l'ennemi demand�
		/// </summary>
		/// <param name="type">Le type d'ennemi � retourner</param>
		/// <returns>Un pointeur d'ennemi selon le type demand�</returns>
		static Ennemi* CreerEnnemi(typesEnnemis type)
		{
			if (type == BASE)
			{
				return new Base();
			}
			else if (type == AMELIORE)
			{
				return new BaseAmelioree();
			}
			else if (type == MULTISHOT)
			{
				return new Multishot();
			}
			else if (type == EVANTAIL)
			{
				return new Evantail();
			}
			else if (type == KAMIKAZE)
			{
				return new Kamikaze();
			}
		}
	private:
		EnnemiFactory();
	};
}
