#pragma once

namespace PewPew
{
	class Controls
	{
	public:
		static bool moveUp;
		static bool moveLeft;
		static bool moveRight;
		static bool moveDown;

		static bool tir;
		static bool changerArme;

		static bool quit;

	private:
		Controls();
	};
}


bool PewPew::Controls::moveUp = false;
bool PewPew::Controls::moveLeft = false;
bool PewPew::Controls::moveRight = false;
bool PewPew::Controls::moveDown = false;
bool PewPew::Controls::tir = false;
bool PewPew::Controls::changerArme = false;
bool PewPew::Controls::quit = false;