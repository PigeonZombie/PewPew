// Classe qui gère les écrans de départ et de fin 
#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
namespace PewPew
{
	class Ecran
	{
	public:
		// Constructeur et destructeur
		Ecran();
		~Ecran();
		// Chargement des textures
		bool Init();
		// Retourne le fond d'écran
		Sprite& GetBackground();
		// Change le fond d'écran
		void SwitchBackground();
	private:
		// Variable qui représente 
		int activeBackground;
		// Sprite de fond d'écran
		Sprite background;
		// Texture de l'écran de début
		Texture tBackground1;
		// Texture de l'écran de fin
		Texture tBackground2;
	};
}


