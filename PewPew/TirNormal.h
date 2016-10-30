#pragma once
#include "Tir.h"

namespace PewPew
{
	class TirNormal : public Tir
	{
	public:
		TirNormal();
		TirNormal(sf::Vector2f* _position, sf::Vector2f* _direction, int _puissance = 0, float _vitesse = 0, int _rotation = 0, bool _joueur=false);		
		virtual ~TirNormal();		
		virtual int Init(sf::Texture &_texture);		
		virtual void Move();
	};
}