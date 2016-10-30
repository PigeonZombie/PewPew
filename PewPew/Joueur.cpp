#include "Joueur.h"
#include <typeindex>
#define OFFEST 5
#define CENTRE 24
using namespace PewPew;
Joueur* Joueur::instance = nullptr;
int Joueur::score;
int Joueur::multiplicateur;

/// <summary>
/// Constructeur privé de la classe Joueur (Singleton)
/// </summary>
Joueur::Joueur()
{
	score = 0;
	thrust = 5;
	vitesse = 8;
	pointsVie = 15;
	estJoueur = true;
	multiplicateur = 1;
	isCharging = false;
	this->armes.Add(new ArmeNormal(0, 10, 1000000, Vector2f(0, 0), true));
	isCharging = false;
}

/// <summary>
/// Mouvement par défaut de la classe abstraite (non-utilisée)
/// </summary>
void Joueur::Mouvement()
{
	move(-vitesse - thrust, 0);
}
/// <summary>
/// Change l'animation du vaisseau qui descend
/// </summary>
void Joueur::Descendre()
{
	if (image < 49)
	{
		image++;

		if (image % 10 == 0)
		{
			rectangleAnimation.left = (rectangleAnimation.width + OFFEST) * (image / 10);
			setTextureRect(rectangleAnimation);
		}
	}
}
/// <summary>
/// Change l'animation du vaisseau qui monte
/// </summary>
void Joueur::Monter()
{
	if (image > 0)
	{
		image--;

		if (image % 10 == 9)
		{
			rectangleAnimation.left = (rectangleAnimation.width + OFFEST) * (image / 10);
			setTextureRect(rectangleAnimation);
		}
	}
}
/// <summary>
/// Change l'animation du vaisseau qui va tout droit
/// </summary>
void Joueur::Centrer()
{
	if (image == CENTRE)
		return;

	if (image < CENTRE)
	{
		Descendre();
	}
	else if (image > CENTRE)
	{
		Monter();
	}
}
/// <summary>
/// Initialise le rectangle d'animation
/// </summary>
void Joueur::InitGraphiques()
{
	rectangleAnimation.width = (getTextureRect().width / 5) - OFFEST;
	rectangleAnimation.height = getTextureRect().height;
	rectangleAnimation.top = 0;
	rectangleAnimation.left = (rectangleAnimation.width + OFFEST) * (image / 10);
	setTextureRect(rectangleAnimation);

	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}
/// <summary>
/// Déplace le joueur selon les touches appuyées
/// </summary>
/// <param name="mouvement">La direction du vaisseau</param>
void Joueur::MouvementJoueur(Vector2i& mouvement)
{
	// Empêcher le joueur de sortir vers la gauche
	if (mouvement.x < 0 && getPosition().x < (0+getGlobalBounds().width/2))
		mouvement.x = 0;
	// Empêcher le joueur de sortir vers la droite
	else if (mouvement.x>0 && getPosition().x>=(LARGEUR-(getGlobalBounds().width*2)))
		mouvement.x = 0;
	// Empêcher le joueur de sortir vers le haut
	if (mouvement.y < 0 && getPosition().y < (0+getGlobalBounds().height/2))
		mouvement.y = 0;
	// Empêcher le joueur de sortir vers la bas
	else if (mouvement.y>0 && getPosition().y >= (HAUTEUR-getGlobalBounds().height/2))
		mouvement.y = 0;

	// Déplacer le vaisseau
	move(mouvement.x * vitesse, mouvement.y * vitesse);
}
/// <summary>
/// Si l'instance de Joueur existe, la retourne. Sinon, crée un nouvelle instance et la retourne.
/// </summary>
/// <returns>L'instance de joueur</returns>
Joueur* Joueur::GetInstance()
{
	if (instance == nullptr)
		instance = new Joueur();
	return instance;
}
/// <summary>
/// Releases this instance.
/// </summary>
void Joueur::Release()
{
	// Supprimer tous les boucliers restants
	while (boucliers.Pop())
	{

	}
	// Supprimer toutes les armes restantes
	for (int i = 0; i < this->armes.GetSize(); i++)
	{
		delete this->armes[i].GetContent();
		this->armes[i].SetContent(nullptr);
	}
	// Supprimer l'instance
	delete instance;
}
/// <summary>
/// Obtient la boîte de collision (à des fins de déboguage seulement)
/// </summary>
/// <returns>Le rectangle de collision rouge</returns>
RectangleShape Joueur::GetCollisionBox()
{
	RectangleShape rect;
	rect.setPosition(getPosition().x, getPosition().y);
	rect.setSize(Vector2f(getTextureRect().width / 2, getTextureRect().height / 2));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Red);
	rect.setFillColor(Color::Transparent);
	rect.rotate(270);
	return rect;
}
/// <summary>
/// Méthode de l'observateur: réagit à une notification du sujet
/// </summary>
/// <param name="sujet">Le sujet.</param>
void Joueur::Notify(Subject* sujet)
{
	// Si c'est un soin, le joueur gagne 5 vies (maximum de 15)
	if (typeid(*sujet) == typeid(Soin))
	{
		Soin *s = (Soin*)sujet;

		if (pointsVie < 15 && s->TesterContact(IntRect(getGlobalBounds())))
		{
			pointsVie += 5;
			if (pointsVie > 15)
				pointsVie = 15;
		}
		// Le soin peut être immédiatement supprimée
		s->Terminer();
	}
	// Si c'est un bouclier, le joueur le ramasse et l'ajoute sur le dessus
	// de sa pile, mais il n'est pas supprimé
	else if (typeid(*sujet) == typeid(Bouclier))
	{
		Bouclier* b = (Bouclier*)sujet;
		if (!b->Collected())
		{
			b->Collect();
			boucliers.Push(b);
			// Le bonus ne doit plus être accessible à l'écran
			b->setTextureRect(IntRect(-20, -20, 0, 0));
		}
	}
	// Si c'est un PointsBonus, le joueur gagne des points 
	else if (typeid(*sujet) == typeid(PointsBonus))
	{
		PointsBonus* p = (PointsBonus*)sujet;
		score += p->GetValeur();
		// Le bonus peut être immédiatement supprimé
		p->Terminer();
	}
	// Si c'est un multiplicateur, le compteur de multiplicateur est incrémenté
	else if (typeid(*sujet) == typeid(Multiplicateur))
	{
		Multiplicateur* m = (Multiplicateur*)sujet; 
		if (m->Collected())
		{
			multiplicateur++;
			m->Collect();
			// Le bonus ne doit plus être accessible à l'écran
			m->setTextureRect(IntRect(-20, -20, 0, 0));
		}
	}
	// Si c'est une bombe explosive et que le joueur est dans un rayon de 300 pixels, 
	// il perd des vies s'il n'a pas un bouclier de la même couleur que la bombe
	else if (typeid(*sujet) == typeid(BombeExplo))
	{
		BombeExplo* b = (BombeExplo*)sujet;
		float distance = sqrtf(pow(b->getPosition().x - getPosition().x, 2.0f) + pow(b->getPosition().y - getPosition().y, 2.0f));
		// La bombe n'a un effet que dans un rayon de 300 
		if (distance < 300)
		{
			if ((GetPremierBouclier() != nullptr && GetPremierBouclier()->GetColor() != b->GetColor())||GetPremierBouclier()==nullptr)
				pointsVie -= (300 - distance) / 8;
		}
	}
	// Ajoute une arme dans la liste
	else if (typeid(*sujet) == typeid(ArmeNormal))
	{
		AjouterArme((ArmeNormal*)sujet);
	}
	else if (typeid(*sujet) == typeid(ArmeNormalPlus))
	{
		AjouterArme((ArmeNormalPlus*)sujet);
	}
	else if (typeid(*sujet) == typeid(ArmeTriangle))
	{
		AjouterArme((ArmeTriangle*)sujet);
	}
	else if (typeid(*sujet) == typeid(ArmeCharge))
	{
		AjouterArme((ArmeCharge*)sujet);
	}
}
/// <summary>
/// Retourne le bouclier sur le dessus de la pile
/// </summary>
Bouclier* Joueur::GetPremierBouclier() const
{
	if (boucliers.GetFirstNode() != nullptr)
		return boucliers.GetFirstNode()->GetContent();
	return nullptr;
}
/// <summary>
/// Ajoute une arme spéciale à la liste
/// </summary>
/// <param name="_arme">L'arme à ajouter</param>
void Joueur::AjouterArme(Arme* _arme)
{
	bool armeDejaAquis = false;
	int index = 0;
	//Vérifier si l'arme est déjà aquis.
	for (int i = 0; i < this->armes.GetSize(); i++)
	{
		//Si oui,
		if (typeid(*this->armes[i].GetContent()) == typeid(*_arme))
		{
			armeDejaAquis = true;
			//Sauvegarder l'index dans la liste.
			index = i;
		}
	}

	//Si l'arme est aquise,
	if (armeDejaAquis)
	{
		//lui ajouter 30 munitions.
		this->armes[index].GetContent()->SetMunitions(this->armes[index].GetContent()->GetMunitions() + 30);
		//this->armes[index].GetContent()->Terminer();
		_arme->Terminer();
	}
	else
	{
		//sinon, l'ajouter à la liste.
		this->armes.Add(_arme);
	}
	// Le bonus ne doit plus être accessible à l'écran 
	_arme->setTextureRect(IntRect(-20, -20, 0, 0));
}
/// <summary>
/// Méthode de tir: tir selon le type d'arme équipée
/// </summary>
/// <returns>Un nouveau projectile</returns>
Tir* Joueur::tirer()
{
	for (int i = 0; i < this->armes.GetSize(); i++)
	{ 
		if (this->armes[i].GetContent()->IsActive())
		{
			Arme* arme = this->armes[i].GetContent();
			Tir* t = nullptr;
			std::type_index* ti = new std::type_index(typeid(Joueur));
			// Tir de l'arme de base
			if (typeid(*arme) == typeid(ArmeNormal))
			{
				if (!isCharging)
				{
					ArmeNormal* a = (ArmeNormal*)this->armes[i].GetContent();
					t = a->Tirer(new Vector2f(this->getPosition()), new Vector2f(1, 0), true);

					a->Notify_Observers(true, true, ti);
				}
			}
			// Tir de l'arme avec projectiles chercheurs
			else if (typeid(*arme) == typeid(ArmeNormalPlus))
			{
				if (!isCharging)
				{
					ArmeNormalPlus* a = (ArmeNormalPlus*)this->armes[i].GetContent();
					t = a->Tirer(new Vector2f(this->getPosition()), new Vector2f(1, 0), true);

					if (this->armes[i].GetContent()->GetMunitions() <= 0)
					{
						this->VerifierMunitions(i);
						this->armes[0].GetContent()->Notify_Observers(true, true, ti);
					}
					else
					{
						a->Notify_Observers(true, true, ti);
					}
				}
			}
			// Tir de l'arme triangle
			else if (typeid(*arme) == typeid(ArmeTriangle))
			{
				if (!isCharging)
				{
					ArmeTriangle* a = (ArmeTriangle*)this->armes[i].GetContent();
					t = a->Tirer(new Vector2f(this->getPosition()), nullptr, true);

					if (this->armes[i].GetContent()->GetMunitions() <= 0)
					{
						this->VerifierMunitions(i);
						this->armes[0].GetContent()->Notify_Observers(true, true, ti);
					}
					else
					{
						a->Notify_Observers(true, true, ti);
					}
				}
			}
			// Tir de l'arme qui charge un tir
			else if (typeid(*arme) == typeid(ArmeCharge))
			{
                if (!isCharging)
				{
 					this->isCharging = true;
 					ArmeCharge* a = (ArmeCharge*)this->armes[i].GetContent();
					t = a->Tirer(new Vector2f(this->getPosition()), new Vector2f(1, 0), true);

					if (this->armes[i].GetContent()->GetMunitions() <= 0)
					{
						this->VerifierMunitions(i);
						this->armes[0].GetContent()->Notify_Observers(true, true, ti);
					}
					else
					{
						a->Notify_Observers(true, true, ti);
					}
				}
			}
			delete ti;
			return t;
		}
	}
	return nullptr;
}
/// <summary>
/// Ajuste la cadence de tir des armes
/// </summary>
void Joueur::UpdateCadences()
{
	for (int i = 0; i < this->armes.GetSize(); i++)
		this->armes[i].GetContent()->SetPeutTirer();
}
/// <summary>
/// Changer d'arme équipée
/// </summary>
/// <returns></returns>
bool Joueur::ChangerArme()
{
	if (this->armes.GetSize() <= 1)
		return false;

	for (int i = 0; i < this->armes.GetSize(); i++)
	{
		if (this->armes[i].GetContent()->IsActive())
		{
			std::type_index* ti = new std::type_index(typeid(Joueur));
			if (!(i == (this->armes.GetSize() - 1)))
			{
				this->armes[i].GetContent()->SetActive(!this->armes[i].GetContent()->IsActive());
				this->armes[(i + 1)].GetContent()->SetActive(!this->armes[(i + 1)].GetContent()->IsActive());
				this->armes[(i + 1)].GetContent()->Notify_Observers(true, true, ti);
				delete ti;
				return true;
			}
			else
			{
				this->armes[i].GetContent()->SetActive(!this->armes[i].GetContent()->IsActive());
				this->armes[0].GetContent()->SetActive(!this->armes[0].GetContent()->IsActive());
				this->armes[0].GetContent()->Notify_Observers(true, true, ti);
				delete ti;
				return true;
			}
			break;
		}
	}

	return false;
}
/// <summary>
/// Vérifie si l'arme a encore des munitions. Si non, elle est retirée de la liste
/// </summary>
/// <param name="_index">The _index.</param>
void Joueur::VerifierMunitions(int _index)
{
	if (this->armes[_index].GetContent()->GetMunitions() <= 0)
	{
		delete this->armes[_index].GetContent();
		this->armes.Remove(_index);
		this->armes[0].GetContent()->SetActive(true);

	}
}
/// <summary>
/// Ajouter des points au score du joueur
/// </summary>
/// <param name="points">Les points à ajouter.</param>
void Joueur::AjouterScore(const int points)
{
	score += points*multiplicateur;
}
/// <summary>
/// Gets the score.
/// </summary>
int Joueur::GetScore()
{
	return score;
}
/// <summary>
/// Gets the multiplier
/// </summary>
int Joueur::GetMultiplicateur()
{
	return multiplicateur;
}
/// <summary>
/// Enlève un multiplicateur
/// </summary>
void Joueur::EnleverMultiplicateur()
{
	multiplicateur--;
}
/// <summary>
/// Retire le bouclier sur le dessus de la pile
/// </summary>
void Joueur::EnleverBouclier()
{
	boucliers.Pop();
}
/// <summary>
/// Change la valeur de isCharging
/// </summary>
/// <param name="_value">La valeur (vrai ou faux)</param>
void Joueur::SetIsCharging(bool _value)
{
	this->isCharging = _value;
}