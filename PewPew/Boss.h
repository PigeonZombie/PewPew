#pragma once
#include "Ennemi.h"

namespace PewPew
{
	class Boss : public Ennemi
	{
	public:
		Boss();
		~Boss();		
		void Mouvement();		
		Tir* tirer();		
		Tir* tirer(Vaisseau* _cible = nullptr);
		void InitGraphiques();		
		void AjouterEnnemi(Ennemi* _ennemi);		
		void Draw(sf::RenderWindow &_window);

		std::vector<Ennemi*> GetGroupe() const;
		sf::IntRect* GetCatchingBox() const;

	private:
		sf::IntRect* catchingBox; //Zone o� les ennemis sont pris par le boss.
		std::vector<Ennemi*> groupe; //Groupe d'ennemis contr�l�s par le boss.
	};
}