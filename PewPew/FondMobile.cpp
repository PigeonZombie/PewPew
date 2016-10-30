#include "FondMobile.h"
using namespace PewPew;
/// <summary>
/// Constructeur de la classe FondMobile. Initialise par d�faut les constantes de dimensions de l'�cran
/// et set la vitesse de d�filement
/// </summary>
/// <param name="vitesse">La vitesse de d�filement.</param>
FondMobile::FondMobile(const int vitesse) : LARGEUR_ECRAN(LARGEUR), HAUTEUR_ECRAN(HAUTEUR), vitesse(vitesse)
{ 
}

/// <summary>
/// Load la texture et set la texture des deux images de fond d'�cran
/// </summary>
/// <param name="path">Le chemin de la texture</param>
/// <returns>Vrai si la texture a load�, faux sinon</returns>
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
/// Augmente la vitesse de d�filement de 1
/// </summary>
void FondMobile::SpeedUp()
{
	vitesse = 6;
}
/// <summary>
/// Diminue la vitesse de d�filement de 1
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
/// Fait d�filer le fond d'�cran
/// </summary>
/// <param name="thrust">Le thrust</param>
void FondMobile::Move(const int thrust)
{
	// Les deux images se d�placent en m�me temps
	fondEcran.move(-vitesse - thrust, 0);
	fondEcran2.move(-vitesse - thrust, 0);
	// Si un fond d'�cran dispara�t compl�tement, il est repositionn� en file derri�re l'autre
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
/// Affiche les deux fond d'�crans
/// </summary>
/// <param name="rw">La fen�tre de jeu</param>
void FondMobile::Draw(RenderWindow* rw)
{
	rw->draw(fondEcran);
	rw->draw(fondEcran2);
}
