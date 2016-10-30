#include "Multishot.h"
using namespace PewPew;

/// <summary>
/// Constructeur de la classe Multishot
/// </summary>
Multishot::Multishot()
{
	pointsVie = 3;
	vitesse = 7;
	//Part vers le haut gauche
	mouvement = Vector2f(-4, -3);
}


Multishot::~Multishot()
{
}
/// <summary>
/// Mouvement du multishot: se déplace droite à gauche en oscillant de haut en bas
/// </summary>
void Multishot::Mouvement()
{
	// Changer de direction verticale si le vaisseau atteint le haut ou le bas de l'écran
	if (getPosition().y >= HAUTEUR - getGlobalBounds().height/2 || getPosition().y <= getGlobalBounds().height+ 30)
		mouvement.y = mouvement.y*-1;
	move(mouvement);
}
/// <summary>
/// Méthode de tir par défaut: non utilisée
/// </summary>
/// <returns>nullptr</returns>
Tir* Multishot::tirer()
{
	return nullptr;
}
/// <summary>
/// Tir du multishot (5 projectiles un par dessus l'autre)
/// </summary>
/// <param name="_k">L'index</param>
/// <returns></returns>
Tir* Multishot::tirer(int _k)
{
	return TirFactory::CreerTir(new Vector2f(this->getPosition().x, (this->getPosition().y - (this->getGlobalBounds().height / 2) + (_k * 30))), new Vector2f(-1, 0), 1, 10);
}
/// <summary>
/// Place la texture dans le sprite et ajuste la taille
/// </summary>
void Multishot::InitGraphiques()
{
	setTexture(tMultishot);
	setScale(0.5f, 0.5f);
	setRotation(270);
	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}
