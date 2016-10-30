#include "Obstacle.h"
using namespace PewPew;

Texture Obstacle::t[5];

/// <summary>
/// Constructeur de la classe obstacle 
/// </summary>
Obstacle::Obstacle() : estDansLeJeu(true)
{
	int texture = rand() % 5;
	setTexture(t[texture]);
	// Déterminer un position et une direction de départ au hasard 
	// Cas 1: part d'en haut et vas vers le bas
	// Cas 2: part d'en bas et vas vers le haut
	int start = rand() % 2;
	// Déterminer au hasard si l'obstacle est destructible ou non
	int _destructible = rand() % 2;
	destructible = _destructible;
	// Position de départ en X
	int x = rand() % (LARGEUR-300);

	// Déterminer la position de départ en Y selon si l'obstacle spawn dans le haut ou le bas de l'écran 
	switch(start)
	{
	case 0:
	{
		int y = (rand() % 50) - 100;
		setPosition(x, y);
		mouvement = Vector2f(GetRandomDirection(-3, 3), GetRandomDirection(1.8f, 2.5f));
		break;
	}
	case 1:
	{
		int y = HAUTEUR + (rand() % 50);
		setPosition(x, y);
		mouvement = Vector2f(GetRandomDirection(-3, 3), GetRandomDirection(-2.5f, -1.8f));
		break;
	}
	default:
		break;
	}
}


Obstacle::~Obstacle()
{
}

/// <summary>
/// Charge toutes les textures d'astéroïdes 
/// </summary>
/// <returns>Vrai si tout est chargé correctement, faux sinon</returns>
bool Obstacle::Init()
{
	bool retour = true;
	if (!t[0].loadFromFile("Sprites\\asteroid_01.png"))
		retour= false;
	if (!t[1].loadFromFile("Sprites\\asteroid_02.png"))
		retour= false;
	if (!t[2].loadFromFile("Sprites\\asteroid_04.png"))
		retour= false;
	if (!t[3].loadFromFile("Sprites\\asteroid_05.png"))
		retour= false;
	if (!t[4].loadFromFile("Sprites\\asteroid_09.png"))
		retour= false;
	return retour;
}

void Obstacle::Notify(Subject* _subject)
{
	if (destructible && typeid(*_subject) == typeid(BombeExplo))
	{
		BombeExplo* b = (BombeExplo*)_subject;
		float distance = sqrtf(pow(b->getPosition().x - getPosition().x, 2.0f) + pow(b->getPosition().y - getPosition().y, 2.0f));
		if (distance<300)
			estDansLeJeu = false;
	}
}

void Obstacle::Move()
{
	move(mouvement);
	Vector2f pos = getPosition();
	// Vérifier si l'obstacle est encore dans les limites du jeu
	if (getPosition().x<200 || getPosition().x >LARGEUR + 200 || getPosition().y < -200 || getPosition().y > HAUTEUR + 200)
		estDansLeJeu = false;
}
//http://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float Obstacle::GetRandomDirection(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return (min + r);
}

bool Obstacle::EstDansLeJeu() const
{
	return estDansLeJeu;
}

bool Obstacle::VerifierCollision(Vaisseau* vaisseau)
{
	if (IntRect(getGlobalBounds()).intersects(vaisseau->GetRect()))
	{
		return true;
	}
	return false;
}