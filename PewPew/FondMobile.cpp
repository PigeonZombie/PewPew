#include "FondMobile.h"
using namespace PewPew;
/// <summary>
/// Constructeur de la classe FondMobile. Initialise par défaut les constantes de dimensions de l'écran
/// et set la vitesse de défilement
/// </summary>
/// <param name="vitesse">La vitesse de défilement.</param>
FondMobile::FondMobile(const int vitesse) : LARGEUR_ECRAN(LARGEUR), HAUTEUR_ECRAN(HAUTEUR), vitesse(vitesse)
{ 
}

/// <summary>
/// Load la texture et set la texture des deux images de fond d'écran
/// </summary>
/// <param name="path">Le chemin de la texture</param>
/// <returns>Vrai si la texture a loadé, faux sinon</returns>
bool FondMobile::SetTexture(const char * path)
{
	if (!fondEcranT.loadFromFile(path))
	{
		return false;
	}

	fondEcran.setTexture(fondEcranT);
	fondEcran.setPosition(0, 0);
	fondEcran2.setTexture(fondEcranT);
	fondEcran2.setPosition(fondEcranT.getSize().x, 0);
}
/// <summary>
/// Augmente la vitesse de défilement de 1
/// </summary>
void FondMobile::SpeedUp()
{
	vitesse = 6;
}
/// <summary>
/// Diminue la vitesse de défilement de 1
/// </summary>
void FondMobile::SlowDown()
{
	vitesse = 4;
}
void FondMobile::ResetSpeed()
{
	vitesse = 5;
}
/// <summary>
/// Fait défiler le fond d'écran
/// </summary>
/// <param name="thrust">Le thrust</param>
void FondMobile::Move(const int thrust)
{
	// Les deux images se déplacent en même temps
	fondEcran.move(-vitesse - thrust, 0);
	fondEcran2.move(-vitesse - thrust, 0);
	// Si un fond d'écran disparaît complètement, il est repositionné en file derrière l'autre
	if (fondEcran.getPosition().x < -fondEcran.getTextureRect().width)
	{
		fondEcran.setPosition(fondEcran2.getPosition().x + fondEcranT.getSize().x, 0);
	}
	if (fondEcran2.getPosition().x < -fondEcran.getTextureRect().width)
	{
		fondEcran2.setPosition(fondEcran.getPosition().x + fondEcranT.getSize().x, 0);
	}
}
/// <summary>
/// Affiche les deux fond d'écrans
/// </summary>
/// <param name="rw">La fenêtre de jeu</param>
void FondMobile::Draw(RenderWindow* rw)
{
	rw->draw(fondEcran);
	rw->draw(fondEcran2);
}
