#include "UI.h"

using namespace PewPew;
Font UI::font;
Text UI::vie;
Text UI::points;
Text UI::bouclier;
Text UI::multiplicateur;
Text UI::arme;
Sprite UI::uiMulti;
Sprite UI::uiPoint;
Sprite UI::uiVie;
Sprite UI::uiBouclier;
Sprite UI::uiArmeActive;
Sprite UI::sArmeActive;
Texture UI::tMulti;
Texture UI::tPoint;
Texture UI::tVie;
Texture UI::tBouclier;
Texture UI::tArme;


int UI::score;
int UI::multi;
int UI::pointBouclier;

/// <summary>
/// Constructeur de la classe UI 
/// </summary>
UI::UI()
{
	// Valeurs par défaut du score, du multiplicateur et des points de vie du bouclier actif
	score = 0;
	multi = 1;
	pointBouclier = 0;
}
/// <summary>
/// Charge la police, les textures de l'interface et initialise tous les textes
/// </summary>
/// <returns>Vrai si tout a correctement chargé, faux sinon</returns>
bool UI::InitGraphiques()
{
	if (!font.loadFromFile("Fonts\\PressStart2P-Regular.ttf"))
		return false;
	if (!tVie.loadFromFile("Sprites\\lives.png"))
		return false;
	if (!tPoint.loadFromFile("Sprites\\score.png"))
		return false;
	if (!tMulti.loadFromFile("Sprites\\multiplier.png"))
		return false;
	if (!tBouclier.loadFromFile("Sprites\\shield.png"))
		return false;
	if (!tArme.loadFromFile("Sprites\\arme.png"))
		return false;
	
	// UI des vies
	vie.setFont(font);
	vie.setColor(Color::Black);
	vie.setCharacterSize(20);
	vie.setPosition(70, 15);
	vie.setString("Vies: ");
	uiVie.setTexture(tVie);
	uiVie.setPosition(0, 0);
	// UI des points
	points.setFont(font);
	points.setColor(Color::Black);
	points.setCharacterSize(20);
	points.setPosition(70, HAUTEUR-35);
	points.setString("Points: "+std::to_string(0));
	uiPoint.setTexture(tPoint);
	uiPoint.setPosition(0, HAUTEUR - 68);
	// UI des multiplicateurs
	multiplicateur.setFont(font);
	multiplicateur.setColor(Color::Black);
	multiplicateur.setCharacterSize(18);
	multiplicateur.setPosition(LARGEUR - 330,HAUTEUR-35);
	multiplicateur.setString("Multi: 1x");
	uiMulti.setTexture(tMulti);
	uiMulti.setPosition(LARGEUR - 500, HAUTEUR - 68);
	// UI du bouclier
	bouclier.setFont(font);
	bouclier.setColor(Color::Black);
	bouclier.setCharacterSize(15);
	bouclier.setString("Aucun bouclier");
	bouclier.setPosition(LARGEUR - 375, 15);
	uiBouclier.setTexture(tBouclier);
	uiBouclier.setPosition(LARGEUR - 500, 0);
	// UI des armes 
	arme.setFont(font);
	arme.setColor(Color::Black);
	arme.setCharacterSize(15);
	arme.setString("Munitions : A lot...");
	arme.setPosition(LARGEUR / 2 - 185, 17);
	sArmeActive.setTexture(*Bonus::GetTArmeNormal());
	sArmeActive.setScale(0.5f, 0.5f);
	sArmeActive.setPosition(LARGEUR / 2 - 235, 10);
	uiArmeActive.setTexture(tArme);
	uiArmeActive.setPosition(LARGEUR / 2 - 250, 0);
}
/// <summary>
/// Change les vies du joueur dans l'interface
/// </summary>
/// <param name="vies">Les vies du joueur</param>
void UI::SetVies(int vies)
{
	vie.setString("Vies: "+std::to_string(vies));
}
/// <summary>
/// Change les points du joueur dans l'interface
/// </summary>
/// <param name="_points">Les points du joueur.</param>
void UI::SetPoints(int _points)
{
	score = _points;
	points.setString("Points: "+std::to_string(score));
}
/// <summary>
/// Change le bouclier actif dans l'interface
/// </summary>
/// <param name="_points">Les points de vie du bouclier</param>
void UI::SetBouclier(int _points)
{
	pointBouclier = _points;
	if (pointBouclier == 0)
		bouclier.setString("Aucun bouclier");
	else 
		bouclier.setString("Résistance: " + std::to_string(pointBouclier));
}
/// <summary>
/// Réinitialise le texte du bouclier s'il le joueur n'en a plus
/// </summary>
void UI::ResetBouclier()
{
	pointBouclier = 0;
	bouclier.setString("Aucun bouclier");
	bouclier.setPosition(LARGEUR - 375, 15);
	bouclier.setColor(Color::Black);
}
/// <summary>
/// Afficher le score en fin de partie
/// </summary>
/// <param name="rw">La fenêtre de jeu</param>
void UI::AfficherScore(RenderWindow* rw)
{
	points.setPosition(LARGEUR / 3, HAUTEUR / 2);
	points.setCharacterSize(34);
	points.setColor(Color::White);
	rw->draw(points);
}
/// <summary>
/// Affiche à l'écran tous les éléments de l'interface 
/// </summary>
/// <param name="rw">La fenêtre de jeu</param>
void UI::Draw(RenderWindow* rw)
{
	rw->draw(uiBouclier);
	rw->draw(bouclier);
	rw->draw(uiMulti);
	rw->draw(uiPoint);
	rw->draw(uiVie);
	rw->draw(vie);
	rw->draw(points);
	rw->draw(multiplicateur);
	rw->draw(uiArmeActive);
	rw->draw(arme);
	rw->draw(sArmeActive);
}
/// <summary>
/// Réagit au signal du sujet passé en paramètre 
/// </summary>
/// <param name="sujet">Le sujet qui a lancé une notification</param>
void UI::Notify(Subject* sujet)
{
	// Ajouter des points si le joueur a ramassé un Point Bonus
	if (typeid(*sujet) == typeid(PointsBonus))
	{
		PointsBonus* b = (PointsBonus*)sujet;
		score += b->GetValeur();
		points.setString("Points: " + std::to_string(score));
	}
	// Changer le multiplicateur si le joueur en a ramassé un
	else if (typeid(*sujet) == typeid(Multiplicateur))
	{
		Multiplicateur* m = (Multiplicateur*)sujet;
		if (m->Collected())
		{
			multi++;
			m->setTextureRect(IntRect(-20, -20, 0, 0));
		}
		// Enlever un multiplicateur quand le bonus se termine
		else if (m->EstTermine())
			multi--;
		multiplicateur.setString("Multi: " + std::to_string(multi) + "X");
	}
	// Afficher le bouclier sur le dessus de la pile 
	else if (typeid(*sujet) == typeid(Bouclier))
	{
		Bouclier* b = (Bouclier*)sujet;
		pointBouclier = b->GetPV();
		bouclier.setString("Résistance: " + std::to_string(pointBouclier));
		bouclier.setColor(b->GetColor());
	}
	// Afficher l'arme active et ses munitions
	else if (typeid(*sujet) == typeid(ArmeNormal))
	{
		ArmeNormal* a = (ArmeNormal*)sujet;
		if (a->IsActive())
		{
			arme.setString("Munitions : A lot...");
			sArmeActive.setTexture(*Bonus::GetTArmeNormal());
		}
	}
	// Afficher l'arme active et ses munitions
	else if (typeid(*sujet) == typeid(ArmeNormalPlus))
	{
		ArmeNormalPlus* a = (ArmeNormalPlus*)sujet;
		if (a->IsActive())
		{
			arme.setString("Munitions : " + std::to_string(a->GetMunitions()));
			sArmeActive.setTexture(*Bonus::GetTArmeNormalPlus());
		}
	}
	// Afficher l'arme active et ses munitions
	else if (typeid(*sujet) == typeid(ArmeTriangle))
	{
		ArmeTriangle* a = (ArmeTriangle*)sujet;
		if (a->IsActive())
		{
			arme.setString("Munitions : " + std::to_string(a->GetMunitions()));
			sArmeActive.setTexture(*Bonus::GetTArmeTriangle());
		}
	}
	// Afficher l'arme active et ses munitions
	else if (typeid(*sujet) == typeid(ArmeCharge))
	{
		ArmeCharge* a = (ArmeCharge*)sujet;
		if (a->IsActive())
		{
			arme.setString("Munitions : " + std::to_string(a->GetMunitions()));
			sArmeActive.setTexture(*Bonus::GetTArmeCharge());
		}
	}
}