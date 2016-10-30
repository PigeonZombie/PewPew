// Classe qui gère l'environnement sonore

#include <SFML\Audio.hpp>
#include <thread>

using namespace sf;
namespace PewPew
{
	static class SoundPlayer
	{
	private:
		// Les 4 sons du jeu
		static Sound son[5];
		// 4 buffers pour les 4 sons
		static SoundBuffer buffers[5];
		// Constructeur
		SoundPlayer();
		// Déclencher un son
		static void StartSound(std::string _son);
		// Indique si la musique de fond doit jouer
		static bool play;
	public: 
		// Charge tous les sons 
		static bool Init();
		// Joue un son 
		static void PlaySound(std::string _son);
		// S'occupe de gérer la musique de fond 
		static void Update();
		// Arrête la musique de fond		
		static void StopPlayingBGMusic();
	};
}