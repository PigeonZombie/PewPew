#include "Boss.h"
#include "TirBoss.h"

using namespace PewPew;

Boss::Boss() : 
	Ennemi()
{
	pointsVie = 15;
}
Boss::~Boss()
{
	std::vector<Ennemi*>::iterator iter;
	for (iter = groupe.begin(); iter < groupe.end(); iter++)
	{
		delete (*iter);
	}
	delete this->catchingBox;
	this->catchingBox = nullptr;
}

/// <summary>
/// D�place tous les ennemis de son vecteur d'ennemis. Les ennemis se d�placent comme le boss et non comme leur mouvement habituel.
/// Arrv� environ au milieu de l'�cran, ils arr�tent de bouger.
/// </summary>
void Boss::Mouvement()
{
	//S,il n'est pas au milieu de l'�cran,
	if (this->getPosition().x >= LARGEUR / 2)
	{
		//D�placer tout le monde.
		std::vector<Ennemi*>::iterator iter;
		for (iter = groupe.begin(); iter < groupe.end(); iter++)
		{
			(*iter)->move(-(1 * this->vitesse), 0);
		}
		//Bouge le boss et sa catchingBox.
		this->move(-(1 * this->vitesse), 0);
		this->catchingBox->left -= (1 * this->vitesse);
	}
}

/// <summary>
/// M�thode inutile, mais qui doit �tre surcharger � cause de l'h�ritage.
/// </summary>
/// <returns>Retourne toujours nullptr.</returns>
Tir* Boss::tirer()
{
	return nullptr;
	
}

/// <summary>
/// Tous les ennemis du vecteur d'ennemis tirent et les tirs sont stock�s dans un TirBoss.
/// </summary>
/// <param name="_cible">Cible pour de potentiels ennemis BaseAm�lior�es.</param>
/// <returns>Retourne le TirBoss, si le vecteur d'ennemis est vide, retourne nullptr.</returns>
Tir* Boss::tirer(Vaisseau* _cible)
{
	if (this->groupe.size() != 0)
	{
		TirBoss* tB = new TirBoss(new Vector2f(this->getPosition()));
		Ennemi* e = (Ennemi*)this;
		tB->AjouterTirs(e, _cible);
		return tB;
	}
	return nullptr;
}

void Boss::InitGraphiques()
{
	setTexture(tBoss);
	setScale(0.2f, 0.2f);
	setRotation(0);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
	this->catchingBox = new sf::IntRect((this->getPosition().x - 50), (this->getPosition().y - 50), ((this->getTexture()->getSize().x / 5) + 100), ((this->getTexture()->getSize().y  / 5) + 100));
}

/// <summary>
/// Ajoute un ennemi au vecteur d'ennemis et augmente le nombre de points de vie du boss du nombre de points de vies de l'ennemis.
/// </summary>
/// <param name="_ennemi">L'ennemi.</param>
void Boss::AjouterEnnemi(Ennemi* _ennemi)
{
	this->groupe.push_back(_ennemi);
	this->pointsVie += _ennemi->GetPV();
}

/// <summary>
/// Dessine toutes les ennemis du vecteur d'ennemis � l'�cran.
/// </summary>
/// <param name="_window">Le fen�tre dans laquelle dessiner les ennemis.</param>
void Boss::Draw(sf::RenderWindow &_window)
{
	_window.draw(*this);

	std::vector<Ennemi*>::iterator iter;
	for (iter = groupe.begin(); iter < groupe.end(); iter++)
	{
		_window.draw((**iter));
	}
}

std::vector<Ennemi*> Boss::GetGroupe() const
{
	return this->groupe;
}

sf::IntRect* Boss::GetCatchingBox() const
{
	return this->catchingBox;
}