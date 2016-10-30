#include "TirFactory.h"

using namespace PewPew;

/// <summary>
/// Crée un tir en fonction du type demandé.
/// </summary>
/// <param name="Position du tir.">The _position.</param>
/// <param name="_direction">Direction du tir.</param>
/// <param name="_puissance">Puissance du tir.</param>
/// <param name="_vitesse">Vitesse du tir.</param>
/// <param name="_rotation">Rotation du tir.</param>
/// <param name="_cible">Cible pour le tir chercheur, si c'est le type voulu.</param>
/// <param name="_type">Le type de tir voulu.</param>
/// <param name="_joueur">Vrai si le tir vient du joueur, faux sinon.</param>
/// <param name="_nbTirs">Nombre de tires si c'est un type TirEvantail qui est voulu.</param>
/// <returns>Retourne le nouveau tir créer.</returns>
Tir* TirFactory::CreerTir(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance, float _vitesse, int _rotation, Vaisseau* _cible, int _type, bool _player, int _nbTirs)
{
	switch (_type)
	{
	case 0:
		return new TirNormal(_position, _direction, _puissance, _vitesse, _rotation, _player);
		break;
	case 1:
		return new TirChercheur(_position, _direction, _puissance, _vitesse, _rotation, _cible, _player);
		break;
	case 2:
		return new TirEvantail(_position, _nbTirs, _puissance, _vitesse, _rotation, _player);
		break;
	case 3:
		return new TirCharge(_position, _direction, _puissance, _vitesse, _rotation, _player);
		break;
	default:
		return nullptr;
	}
	return nullptr;
}