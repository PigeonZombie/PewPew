// Classe qui g�re les �crans de d�part et de fin 
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
		// Retourne le fond d'�cran
		Sprite& GetBackground();
		// Change le fond d'�cran
		void SwitchBackground();
	private:
		// Variable qui repr�sente 
		int activeBackground;
		// Sprite de fond d'�cran
		Sprite background;
		// Texture de l'�cran de d�but
		Texture tBackground1;
		// Texture de l'�cran de fin
		Texture tBackground2;
	};
}


