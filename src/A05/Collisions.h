#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>	// Fons de pantalla - personatges - moviment
#include <SDL_ttf.h>	// Font import
#include <SDL_mixer.h>	// SOund library
#include <time.h>		//for delta time implementation
#include <iostream>



namespace Collision {

	bool HasCollided(SDL_Rect Origen, SDL_Rect Target) {


		/*return ((goldRect5.x + goldRect5.w) >= (playerOne.x) &&
		(goldRect5.x) <= (playerOne.x + playerOne.w) &&
		(goldRect5.y + goldRect5.h) >= (playerOne.y) &&
		(goldRect5.y) <= (playerOne.y + playerOne.h))*/

		return false;

	}


	bool HasCollidedWithWalls(SDL_Rect inside, SDL_Rect container) {


		return false;
	}
}