#pragma once

namespace PewPew
{
	// Le nombre maximum de projectile qu'il peut y avoir simultanément à l'écran
	const int NB_MAX_TIRS = 500;
	// Les types d'ennemis possibles
	enum typesEnnemis { BASE, AMELIORE, MULTISHOT, EVANTAIL, KAMIKAZE };
	// Largeur de l'écran
	const int LARGEUR = 1380;
	// Hauteur de l'écran
	const int HAUTEUR = 720;
	// Le nombre maximal de bonus affiché à l'écran simultanément 
	const int MAX_NB_BONUS = 10;
	// La rayon du bouclier du joueur
	const int RAYON_BOUCLIER = 30;
	// Le nombre maximal d'astéroïdes simultanément à l'écran 
	const int NB_MAX_OBSTACLE = 5;
}
