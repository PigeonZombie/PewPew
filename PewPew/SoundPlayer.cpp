#include "SoundPlayer.h"

using namespace PewPew;
Sound SoundPlayer::son[5];
SoundBuffer SoundPlayer::buffers[5];
bool SoundPlayer::play = true;
SoundPlayer::SoundPlayer()
{
	play = true;
}
/// <summary>
/// Charge tous les sons
/// </summary>
/// <returns>Vrai si tout a été correctement chargé, faux sinon</returns>
bool SoundPlayer::Init()
{
	if (!buffers[0].loadFromFile("Sounds\\laserJoueur.ogg"))
		return false;
	if (!buffers[1].loadFromFile("Sounds\\selectSound.ogg"))
		return false;
	if (!buffers[2].loadFromFile("Sounds\\laserEnnemi.ogg"))
		return false;
	if (!buffers[3].loadFromFile("Sounds\\bgMusic.ogg"))
		return false;
	if (!buffers[4].loadFromFile("Sounds\\The Choice.ogg"))
		return false;
	son[0].setBuffer(buffers[0]);
	son[1].setBuffer(buffers[1]);
	son[2].setBuffer(buffers[2]);
	son[3].setBuffer(buffers[3]);
	son[4].setBuffer(buffers[4]);
	return true;
}
/// <summary>
/// Part un nouveau thread qui va jouer un son
/// </summary>
/// <param name="_son">The son à joueur </param>
void SoundPlayer::PlaySound(std::string _son)
{
	std::thread t(StartSound,_son);
	t.join();
}
/// <summary>
/// Part la chanson principale du jeu si elle est arrêtée (donc joue en boucle)
/// </summary>
void SoundPlayer::Update()
{
	if (son[3].getStatus()==Sound::Stopped && play)
		son[3].play();
}
/// <summary>
/// Déclenche un son 
/// </summary>
/// <param name="_son">Le son à jouer</param>
void SoundPlayer::StartSound(std::string _son)
{
	if (_son == "tirJoueur")
		son[0].play();
	else if (_son == "select")
		son[1].play();
	else if (_son == "tirEnnemi")
		son[2].play();
	else if (_son == "The Choice")
		son[4].play();
}
/// <summary>
/// Arrête de jouer la musique de fond
/// </summary>
void SoundPlayer::StopPlayingBGMusic()
{
	play = false;
	son[3].stop();
}