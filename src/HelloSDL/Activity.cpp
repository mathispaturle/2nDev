#pragma once
#include <iostream>
#include <time.h>
#include "SDL.h"

#define RECT_SIZE 20
#define WIDTH 800
#define HEIGHT 600
#define NEUTRAL 0

struct Vector2D {
	int x;
	int y;
	Vector2D::Vector2D() :x(10), y(10) {};
	Vector2D::Vector2D(int uX, int uY) :x(uX), y(uY) {};

	Vector2D& operator+=(const Vector2D& a) {
		//TO DO
	}
};

void sleep(int milliseconds) {
	clock_t time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end);
}

void randomColor(SDL_Color &col) {
	col.r = rand() % 255;
	col.g = rand() % 255;
	col.b = rand() % 255;
}

int main(int argc, char *argv[]) {

	int nMod = 1;

	int xMod = 1;
	int yMod = 1;
	int speed = 1;

	SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	Vector2D position = Vector2D(100, 100);
	SDL_Color color = { 0,255,0, 0xFF };

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: quit = SDL_TRUE; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: quit = SDL_TRUE; break;
				}
				break;
			}
		}

		//Update
		randomColor(color);
		//TO DO
		sleep(2);

		//Background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);
		//Rect
		SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 0);


		
		if (position.x >= (WIDTH - RECT_SIZE)){
			xMod = -nMod;
		}

		else if (position.x <= NEUTRAL) {
			xMod = nMod;
		}

		else if (position.y <= NEUTRAL) {
			yMod = nMod;
		}

		else if (position.y >= HEIGHT - RECT_SIZE){
			yMod = -nMod;
		}

		position.x += speed*xMod;
		position.y += speed*yMod;

		
		SDL_RenderFillRect(renderer, new SDL_Rect{ position.x, position.y, RECT_SIZE, RECT_SIZE });
		SDL_RenderPresent(renderer);
		
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return 0;
}