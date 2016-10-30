#pragma once
#include "Tir.h"
#include "TirFactory.h"
#include "Bonus.h"

namespace PewPew
{	
	/// <summary>
	/// Permet de tirer  d'un type de tire en particulier.
	/// </summary>
	class Arme : public Bonus
	{
	protected:
		const int TYPE_TIR; //Le type de tir effectué par l'arme.
		const int CADENCE_TIR; //La vitesse à laquelle l'arme peut tirer.
		int peutTirer; //vrai si l'arme peut tirer, faux sinon.
		int munitions; //Nombre de munitions dans l'arme.
		//Ne pas mélanger avec la variable "actif" de bonus.
		//Celle-ci sert à définir quel arme utilise le joueur.
		bool active; //Vrai si c'est l'arme que le joueur utilise. Faux sinon.

	public:
		Arme(int _typeTir, int _cadence, int _munitions, Vector2f &_position, bool _active);

		virtual void InitGraphiques() = 0;
		virtual void Action() = 0;		
		virtual Tir* Tirer(sf::Vector2f* _p, sf::Vector2f* _d, bool _player = false) = 0;

		int GetMunitions() const;
		bool IsActive() const;

		void SetActive(bool _value);
		void SetPeutTirer();
		void SetMunitions(int _value);
	};
}