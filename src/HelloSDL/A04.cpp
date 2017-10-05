#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <SDL.h>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 480

#define POINTS_E 7
#define POINTS_N 4
#define POINTS_T 5
#define POINTS_I 2
#define POINTS_U 4
#define POINTS_B 12

#define SQUARE_SIZE 70
#define OFFSET_SQUARE 10
#define START_SQUARE_Y 170

#define ASSERT(cnd, msg) if (cnd) throw std::exception(&(msg)[0]);

static SDL_Point GletterE[POINTS_E] = { { 100, 50 },	//superior right point
										{ 50, 50 },		//superior left point
										{ 50, 100 },	//middle left point
										{ 100, 100 },	//middle right point
										{ 50, 100 },	//middle left point
										{ 50, 150 },	//lower left point
										{ 100, 150 }	//lower right point
};

static SDL_Point GletterN[POINTS_N] = { { 150, 150 },	//lower left point
										{ 150, 50 },	//upper left point
										{ 200, 150 },	//lower right point
										{ 200, 50 }		//upper right point
};

static SDL_Point GletterT[POINTS_T] = { {250, 50},		//upper left point
										{275, 50},		//upper middle point
										{275, 150},		//lower middle point
										{275, 50},		//upper middle point
										{300, 50}		//upper right point

};

static SDL_Point GletterI[POINTS_I] = { {350, 50},		//upper point		
										{350, 150}		//lower point
};

static SDL_Point GletterU[POINTS_U] = { { 500, 50 },		//upper leftpoint		
										{ 500, 150 },		//lower left point
										{ 550, 150 },		//lower left point
									    { 550, 50 },		//upper right point

};

static SDL_Point GletterB[POINTS_B] = { { 600, 50 },	//1 superior left point
										{ 640, 50 },	//2 superior right point(1)
										{ 650, 60 },	//3 superior diagonal point (1)
										{ 650, 90 },	//4 superior diagonal point (2)
										{ 640, 100 },	//5 superior right point(2)
										{ 600, 100 },	//6 middle left point
										{ 600, 50 },	//7 superior left point
										{ 600, 150 },	//8 lower left point
										{ 640, 150 },	//9 lower right point
										{ 650, 140 },	//10 lower diagonal point (1)
										{ 650, 110 },	//11 lower diagonal point (2)
										{ 640, 100 },	//12 lower last right point
};


int main(int argc, char* argv[])
{

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Init
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) std::cout << "Window could not be created!" << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) std::cout << "Renderer could not be created!" << std::endl;

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = SDL_TRUE;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					quit = SDL_TRUE;
					break;
				}
				break;
			}
		}
		//Background
		SDL_SetRenderDrawColor(renderer, 20, 50, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		//ENTI-UB
		SDL_SetRenderDrawColor(renderer, 255, 50, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(renderer, GletterE, POINTS_E);
		SDL_RenderDrawLines(renderer, GletterN, POINTS_N);
		SDL_RenderDrawLines(renderer, GletterT, POINTS_T);
		SDL_RenderDrawLines(renderer, GletterI, POINTS_I);

		SDL_RenderDrawLines(renderer, GletterU, POINTS_U);
		SDL_RenderDrawLines(renderer, GletterB, POINTS_B);
		
		SDL_RenderDrawLine(renderer, 400, 100, 450, 100);

		//LOGO
		SDL_SetRenderDrawColor(renderer, 105, 0, 150, SDL_ALPHA_OPAQUE);
		SDL_Rect rec1 = { SCREEN_WIDTH/2 - SQUARE_SIZE/2, START_SQUARE_Y, SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);;

		rec1 = { SCREEN_WIDTH / 2 - SQUARE_SIZE / 2, START_SQUARE_Y + 2 * SQUARE_SIZE + 2 * OFFSET_SQUARE,SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);


		SDL_SetRenderDrawColor(renderer, 190, 190, 190, SDL_ALPHA_OPAQUE);
		rec1 = { SCREEN_WIDTH / 2 + OFFSET_SQUARE + SQUARE_SIZE/2, START_SQUARE_Y, SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);;

		rec1 = { SCREEN_WIDTH / 2 - SQUARE_SIZE / 2, START_SQUARE_Y + SQUARE_SIZE + OFFSET_SQUARE, SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);;

		rec1 = { SCREEN_WIDTH / 2 - SQUARE_SIZE/2 -SQUARE_SIZE - OFFSET_SQUARE, START_SQUARE_Y + SQUARE_SIZE + OFFSET_SQUARE, SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);;

		rec1 = { SCREEN_WIDTH / 2 + OFFSET_SQUARE + SQUARE_SIZE / 2, START_SQUARE_Y + 2*SQUARE_SIZE + 2 * OFFSET_SQUARE,SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &rec1);
	
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return 0;
}