#include "TirBoss.h"
#include "TirChercheur.h"
#include "Boss.h"
#include "BaseAmelioree.h"

using namespace PewPew;

TirBoss::TirBoss(sf::Vector2f* _position) :
	Tir(_position, nullptr)
{

}

TirBoss::~TirBoss()
{
	//Delete tous les tirs de la listes.
	for (int i = 0; i < this->tirs.GetSize(); i++)
		if (this->tirs[i].GetContent() != nullptr)
			delete this->tirs[i].GetContent();

	//Delete la position initial des tirs.
	if (this->position != nullptr)
	{
		delete this->position;
		this->position = nullptr;
	}
}

int TirBoss::Init(sf::Texture &_texture)
{
	if (&_texture == nullptr)
		return EXIT_FAILURE;
	if (this->tirs.GetSize() == 0)
		return EXIT_FAILURE;

	//Initialise tous les tirs de la liste.
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		this->tirs[i].GetContent()->Init(_texture);
	}
	
	return EXIT_SUCCESS;
}

void TirBoss::Move()
{
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		this->tirs[i].GetContent()->Move();
	}
}

bool TirBoss::VerifierCollision(Vaisseau* _ship)
{
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		if (this->tirs[i].GetContent()->VerifierCollision(_ship))
		{
			delete this->tirs[i].GetContent();
			this->tirs.Remove(i);
		}
	}
	return false;
}

/// <summary>
/// Ajoute tous les tirs des vaisseaux contr�l�s par le _boss.
/// </summary>
/// <param name="_boss">Boss qui effectu le tir.</param>
/// <param name="_cible">Cible � utiliser pour de potentiels TirChercheurs.</param>
void TirBoss::AjouterTirs(Ennemi* _boss, Vaisseau* _cible)
{
	Boss* b = (Boss*)_boss;
	std::vector<Ennemi*>::iterator iter;
	std::vector<Ennemi*> groupe = b->GetGroupe();

	//Pour chaque ennemis dans le vector du boss,
	for (iter = groupe.begin(); iter < groupe.end(); iter++)
	{
		//Effectu� un tir.
		Tir* t = (*iter)->tirer();
		//Si le tir a �t� effectu� correctement,
		if (t != nullptr)
		{
			//Si c'est un vaisseau qui tir des tirs chercheurs,
			if (typeid((**iter)) == typeid(BaseAmelioree))
			{
				TirChercheur* tC = (TirChercheur*)t;
				//donn� une cible au tir.
				tC->SetCible(_cible);
			}
			//Ajouter le tir � la fameuse liste de tires
			this->tirs.Add(t);
		}
	}
}

void TirBoss::Draw(sf::RenderWindow &_window)
{
	for (int i = 0; i < this->tirs.GetSize(); i++)
	{
		//Si c'est un tir �vantail, il doit dessiner chacun de ses tirs � l'�cran.
		if (typeid(*this->tirs[i].GetContent()) == typeid(TirEvantail))
		{
			TirEvantail* tE = (TirEvantail*)this->tirs[i].GetContent();
			tE->Draw(_window);
		}
		else
			_window.draw(*this->tirs[i].GetContent());
	}
}