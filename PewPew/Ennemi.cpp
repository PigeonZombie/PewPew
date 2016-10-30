#include "Ennemi.h"
#define OFFEST 5
#define CENTRE 24

using namespace PewPew;

Texture Ennemi::tBase;
Texture Ennemi::tBaseAmelioree;
Texture Ennemi::tMultishot;
Texture Ennemi::tEvantail;
Texture Ennemi::tKamikaze;
Texture Ennemi::tBoss;

/// <summary>
/// Constructeur de la classe Ennemi
/// </summary>
Ennemi::Ennemi()
{
	vitesse = 6;
	pointsVie = 5;
	time = 0;
	valeur = pointsVie * 10;
	setPosition(LARGEUR, GetRandomDirection(200, HAUTEUR-200));
}


Ennemi::~Ennemi()
{
}

/// <summary>
/// Charge toutes les textures des ennemis
/// </summary>
/// <returns>Vrai si tout est correctement chargé, faux sinon</returns>
bool Ennemi::LoadShips()
{
	if (!tBase.loadFromFile("Sprites\\base.png"))
	{
		return false;
	}
	if (!tBaseAmelioree.loadFromFile("Sprites\\baseamelioree.png"))
	{
		return false;
	}
	if (!tMultishot.loadFromFile("Sprites\\multishot.png"))
	{
		return false;
	}
	if (!tEvantail.loadFromFile("Sprites\\evantail.png"))
	{
		return false;
	}
	if (!tKamikaze.loadFromFile("Sprites\\kamikaze.png"))
	{
		return false;
	}
	if (!tBoss.loadFromFile("Sprites\\boss.png"))
	{
		return false;
	}
	return true;
}
/// <summary>
/// Détermine si le vaisseau ennemi est en collision avec le joueur
/// </summary>
/// <param name="rectJoueur">Le rectangle du joueur</param>
/// <returns>Vrai s'il y a collision, faux sinon</returns>
bool Ennemi::VerifierCollisionAvecJoueur(const IntRect rectJoueur)
{
	//IntRect rect(getPosition().x, getPosition().y, getTextureRect().height/2, getTextureRect().width/2);
	IntRect rect = IntRect(this->getGlobalBounds());
	if (rect.intersects(rectJoueur))
	{
		return true;
	}
}
/// <summary>
/// Retourne la boîte de collision du vaisseau (à des fins de déboguage seulement)
/// </summary>
/// <returns>Le rectangle de couleur rouge</returns>
RectangleShape Ennemi::GetCollisionBox()
{
	RectangleShape rect;
	rect.setPosition(getPosition().x, getPosition().y);
	rect.setSize(Vector2f(getTextureRect().width/2,getTextureRect().height/2));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Red);
	rect.setFillColor(Color::Transparent);
	rect.rotate(270);
	return rect;
}
/// <summary>
/// Pour l'observateur: réagir à une notification d'un sujet
/// </summary>
/// <param name="sujet">Le sujet.</param>
void Ennemi::Notify(Subject* sujet)
{
	// Une bombe explosive cause des dommages à tout vaisseau dans un rayon de 300 pixels
	if (typeid(*sujet) == typeid(BombeExplo))
	{
		BombeExplo* b = (BombeExplo*)sujet;
		float distance = sqrtf(pow(b->getPosition().x - getPosition().x, 2.0f) + pow(b->getPosition().y - getPosition().y, 2.0f));
		// La bombe n'a un effet que dans un rayon de 300 
		if (distance < 300)
		{
			pointsVie -= (300 - distance) / 8;
		}
	}
	// Une bombe magnétique empêche les ennemis de tirer pour 3 séquences de 60 frames (180 frames)
	else if (typeid(*sujet) == typeid(BombeMagnetique))
	{
		canShoot = false;
		time++;
		if (time == 60*3)
		{
			BombeMagnetique* m = (BombeMagnetique*)sujet;
			m->Terminer();
			canShoot = true;
		}
	}
}
/// <summary>
/// Determines whether this instance can shoot.
/// </summary>
/// <returns>True if the ennemy can shoot, false otherwise</returns>
bool Ennemi::CanShoot() const
{
	return canShoot;
}
/// <summary>
/// Retourne la valeur en points du vaisseau ennemi
/// </summary>
/// <returns>La valeur</returns>
int Ennemi::GetPoints() const
{
	return valeur;
}

//http://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
/// <summary>
/// Obtient un nombre flottant aléatoire dans une plage 
/// </summary>
/// <param name="min">Le nombre minimum</param>
/// <param name="max">Le nombre maximum</param>
/// <returns>Un flottant entre le minimum et le maximum</returns>
float Ennemi::GetRandomDirection(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return (min + r);
}
