#include <vld.h>
#include "Game.h"
#include "Pile.h"
//#include "List.h"
#include <assert.h>
#include <time.h>

PewPew::Game game;


int main()
{
	srand(time(NULL));
	// Tests de pile
	myns::Pile<int> maPile;
	maPile.Pop();
	int* nb1 = new int(-20);
	int* nb2 = new int(10);
	maPile.Push(nb1);
	maPile.Push(nb2);
	maPile.Pop();
	maPile.Pop();
	assert(maPile.GetFirstNode() == nullptr);
	delete nb1;
	delete nb2;

	// Démarrage du jeu
	game.Run();
}