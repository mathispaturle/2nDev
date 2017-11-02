#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>	// Fons de pantalla - personatges - moviment
#include <SDL_ttf.h>	// Font import
#include <SDL_mixer.h>	// SOund library
#include <time.h>		//for delta time implementation
#include <iostream>


//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60
#define TERRAINLIMIT 180
#define GOLD_WIDTH 50
#define GOLD_HEIGHT 50
#define PLAYERWIDTH 350
#define PLAYERHEIGHT 189
#define OFFSET 50
#define RECTSIZE 100
#define AMOUNT 5
#define MAXAMOUNT 5

//SDL DECLARATIONS
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Keycode keyPressed;
SDL_Texture *bgTexture;

SDL_Rect bgRectS1{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Rect bgRectS2{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Rect spriteRectOne, spriteRectTwo;

SDL_Rect playerOne{ OFFSET, SCREEN_HEIGHT / 2, RECTSIZE, RECTSIZE };
SDL_Rect playerTwo{ SCREEN_WIDTH - OFFSET - RECTSIZE, SCREEN_HEIGHT / 2, RECTSIZE, RECTSIZE };

enum class GameState { PLAY, EXIT, MENU };
enum class MOVEINPUT {W, A, S, D, UP, DOWN, LEFT, RIGHT};
GameState gamestat;
MOVEINPUT move;
MOVEINPUT move2;

//INIT IMG
const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };


int frameTime = 0;
int textWidth, textHeigth, framewidth, frameheight;

bool renderGold1, renderGold2, renderGold3, renderGold4, renderGold5;
int puntuacioOne = 0;
int overallPuntuacion = 0;



#pragma region "EventHandlePlay"
void EventHandlePlay() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			//isRunning = false;
			gamestat = GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				move = MOVEINPUT::W;
				break;
			case SDLK_a:
				move = MOVEINPUT::A;
				break;
			case SDLK_s:
				move = MOVEINPUT::S;
				break;
			case SDLK_d:
				move = MOVEINPUT::D;
				break;
			case SDLK_LEFT:
				move2 = MOVEINPUT::LEFT;
			case SDLK_RIGHT:
				move2 = MOVEINPUT::RIGHT;
				break;
			case SDLK_UP:
				move2 = MOVEINPUT::UP;
				break;
			case SDLK_DOWN:
				move2 = MOVEINPUT::DOWN;
				break;

			}

		default:;
		}
	}
}
#pragma endregion


#pragma region "UpdatePlay"
void UpdatePlay() {

	switch (move) {


	case MOVEINPUT::W:
		if (playerOne.y > TERRAINLIMIT)
		{
			//std::cout << "A key was pressed... w" << std::endl;

			float row = frameheight;
			playerOne.y -= AMOUNT;
			frameheight *= 3;
			spriteRectOne.y = frameheight;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRectOne.x += framewidth;
				if (spriteRectOne.x >= framewidth * 3)
					spriteRectOne.x = 0;
			}
			frameheight = row;

		}
		break;
	case MOVEINPUT::A:
		if (playerOne.x > 0)
		{
			//std::cout << "A key was pressed... a" << std::endl;

			float row = frameheight;
			playerOne.x -= AMOUNT;
			frameheight *= 1;
			spriteRectOne.y = frameheight;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRectOne.x += framewidth;
				if (spriteRectOne.x >= framewidth * 3)
					spriteRectOne.x = 0;
			}
			frameheight = row;
		}
		break;
	case MOVEINPUT::S:
		if (playerOne.y < (SCREEN_HEIGHT - spriteRectOne.h))
		{
			//std::cout << "A key was pressed... s" << std::endl;

			float row = frameheight;
			playerOne.y += AMOUNT;
			frameheight *= 0;
			spriteRectOne.y = frameheight;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRectOne.x += framewidth;
				if (spriteRectOne.x >= framewidth * 3)
					spriteRectOne.x = 0;
			}
			frameheight = row;
		}
		break;
	case MOVEINPUT::D:
		if (playerOne.x < (SCREEN_WIDTH - spriteRectOne.w))
		{
			//std::cout << "A key was pressed... d" << std::endl;

			float row = frameheight;
			playerOne.x += AMOUNT;
			frameheight *= 2;
			spriteRectOne.y = frameheight;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRectOne.x += framewidth;
				if (spriteRectOne.x >= framewidth * 3)
					spriteRectOne.x = 0;
			}
			frameheight = row;
		}
		break;


	}
	switch (move2)
	{
	case MOVEINPUT::LEFT:
		//std::cout << "A key was pressed... left" << std::endl;
		//playerTwo.x -= AMOUNT;
		if (playerOne.x < (SCREEN_WIDTH - spriteRectOne.w))
		{
			//std::cout << "A key was pressed... d" << std::endl;

			float row = frameheight;
			playerTwo.x -= AMOUNT;
			frameheight *= 2;
			spriteRectTwo.y = frameheight;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRectOne.x += framewidth;
				if (playerTwo.x >= framewidth * 3)
					playerTwo.x = 0;
			}
			frameheight = row;
		}
		break;
	case MOVEINPUT::RIGHT:
		//std::cout << "A key was pressed... right" << std::endl;
		playerTwo.x += AMOUNT;
		break;
	case MOVEINPUT::UP:
		
		//std::cout << "A key was pressed... up" << std::endl;
		playerTwo.y -= AMOUNT;
		
		break;
	case MOVEINPUT::DOWN:
		//std::cout << "A key was pressed... down" << std::endl;
		playerTwo.y += AMOUNT;
		break;

	}

	
}
#pragma endregion


#pragma region "DrawPlay"
void DrawPlay() {

}
#pragma endregion



#pragma region "EventHandleMenu"
void EventHandleMenu() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			//isRunning = false;
			gamestat = GameState::EXIT;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//std::cout << "Button was pressed at x: " << event.motion.x << " and y: " << event.motion.y << std::endl;
		default:
			break;
		}
	}

}
#pragma endregion

#pragma region "UpdateMenu"
void UpdateMenu() {}
#pragma endregion

#pragma region "DrawMenu"
void DrawMenu() {


}
#pragma endregion




int main(int, char*[]) {

#pragma region "Initializations Region"
	/*
	*
	*	--- INIT ---
	*
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	//Throw error if no flags are found
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error, SDL_image init";

	// TTF initialization
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf.h";

	// Mix Initialization
	//if (Mix_Init(mixFlags) & mixFlags) throw "No es pot inicialitzar SDL_mixer.h";

	clock_t lastTime = clock();
	float timeDown = 10.;
	float deltaTime = 0;
	bool isHoverPlay = false;
	bool isHoverExit = false;
	renderGold1 = renderGold2 = renderGold3 = renderGold4 = renderGold5 = true;

#pragma endregion

#pragma region "Window Region"
	/*
	*
	*	--- WINDOW ---
	*
	*/
	window = { SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

#pragma endregion

#pragma region "Renderer Region"
	/*
	*
	*	--- RENDERER ---
	*
	*/

	renderer = { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";


#pragma endregion


	//Backgrond Scene 1
	SDL_Texture *bgTextureBG1{ IMG_LoadTexture(renderer, "../../GameProject/res/img/bg.jpg") }; //Init of a texture
	if (bgTextureBG1 == nullptr)throw "Can't load the background image"; // Error load throw

																		 //Background Scene 2
	SDL_Texture *bgTextureBG2{ IMG_LoadTexture(renderer, "../../GameProject/res/img/bgCastle.jpg") }; //Init of a texture
	if (bgTextureBG2 == nullptr)throw "Can't load the background image"; // Error load throw

																		 //Gold
	SDL_Texture*goldTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/gold.png") }; //Init of a texture
	if (goldTexture == nullptr) throw "Can't load goldTexture"; // Error load throw

	int goldWidth, goldHeight;

	// Init gold in random positions
	srand(time(NULL));


	

	SDL_Rect goldRect1{ rand() % SCREEN_WIDTH + 1 - GOLD_WIDTH, rand() % (SCREEN_HEIGHT - TERRAINLIMIT) + TERRAINLIMIT - GOLD_HEIGHT, GOLD_WIDTH, GOLD_HEIGHT };
	SDL_Rect goldRect2{ rand() % SCREEN_WIDTH + 1 - GOLD_WIDTH, rand() % (SCREEN_HEIGHT - TERRAINLIMIT) + TERRAINLIMIT - GOLD_HEIGHT, GOLD_WIDTH, GOLD_HEIGHT };
	SDL_Rect goldRect3{ rand() % SCREEN_WIDTH + 1 - GOLD_WIDTH, rand() % (SCREEN_HEIGHT - TERRAINLIMIT) + TERRAINLIMIT - GOLD_HEIGHT, GOLD_WIDTH, GOLD_HEIGHT };
	SDL_Rect goldRect4{ rand() % SCREEN_WIDTH + 1 - GOLD_WIDTH, rand() % (SCREEN_HEIGHT - TERRAINLIMIT) + TERRAINLIMIT - GOLD_HEIGHT, GOLD_WIDTH, GOLD_HEIGHT };
	SDL_Rect goldRect5{ rand() % SCREEN_WIDTH + 1 - GOLD_WIDTH, rand() % (SCREEN_HEIGHT - TERRAINLIMIT) + TERRAINLIMIT - GOLD_HEIGHT, GOLD_WIDTH, GOLD_HEIGHT };
	



	// ---Animated Sprites---
#pragma region "Players"
	//Animation
	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/spCastle.png") };//Player1
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeigth);

	framewidth = textWidth / 12;
	frameheight = textHeigth / 8;
	playerOne.x = playerOne.y = 450;
	playerTwo.x = playerTwo.y = 250;
	spriteRectOne.x = spriteRectOne.y = 0;
	spriteRectTwo.x = framewidth * 7;
	spriteRectTwo.y = frameheight * 4;
	playerOne.w = spriteRectOne.w = framewidth;
	playerOne.h = spriteRectOne.h = frameheight;
	playerTwo.w = spriteRectTwo.w = framewidth;
	playerTwo.h = spriteRectTwo.h = frameheight;

#pragma endregion

#pragma region "Text"
	//Open Font
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_TTF";
	TTF_Font *font{ TTF_OpenFont("../../GameProject/res/ttf/saiyan.ttf",100) }; // Crea fuente
	if (font == nullptr)throw "Can't open the saiyan font";

	//Play Text
	SDL_Surface *tmpPlaySurface{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 0,150,0,1 }) }; // Crea una surface
	if (tmpPlaySurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textPlayTexture{ SDL_CreateTextureFromSurface(renderer,tmpPlaySurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textPlayRect{ 325,100,tmpPlaySurface->w,tmpPlaySurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpPlaySurface);
	// Play Text Hover
	SDL_Surface *tmpPlaySurface2{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 0,200,0,1 }) }; // Crea una surface
	if (tmpPlaySurface2 == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textPlayTexture2{ SDL_CreateTextureFromSurface(renderer,tmpPlaySurface2) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textPlayRect2{ 325,100,tmpPlaySurface2->w,tmpPlaySurface2->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpPlaySurface2);

	// Exit text
	SDL_Surface *tmpStopSurface{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 230,0,0,1 }) }; // Crea una surface
	if (tmpStopSurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textStopTexture{ SDL_CreateTextureFromSurface(renderer,tmpStopSurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textStopRect{ 325,250,tmpStopSurface->w,tmpStopSurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpStopSurface);
	// Exit Text Hover
	SDL_Surface *tmpStopSurfaceHover{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 255,102,102,1 }) }; // Crea una surface
	if (tmpStopSurfaceHover == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textStopTexture2{ SDL_CreateTextureFromSurface(renderer,tmpStopSurfaceHover) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textStopRect2{ 325,250,tmpStopSurfaceHover->w,tmpStopSurfaceHover->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpStopSurfaceHover);

	TTF_CloseFont(font);

#pragma endregion




#pragma region "Game Loop Region"
	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	gamestat = GameState::MENU;

	//while (isRunning){

	while (gamestat != GameState::EXIT) {

		switch (gamestat) {

		case GameState::PLAY:
			EventHandlePlay();

			/*-------*/
			UpdatePlay();

			//colision goldRect1 with player 1
			if ((goldRect1.x + goldRect1.w) >= (playerOne.x) &&
				(goldRect1.x) <= (playerOne.x + playerOne.w) &&
				(goldRect1.y + goldRect1.h) >= (playerOne.y) &&
				(goldRect1.y) <= (playerOne.y + playerOne.h))
			{
				//std::cout << "Gold Bag 1 taken" << std::endl;
				if (renderGold1) {
					puntuacioOne++;
					overallPuntuacion++;
				}

				renderGold1 = false;
			}

			//colision goldRect2 with player 1
			if ((goldRect2.x + goldRect2.w) >= (playerOne.x) &&
				(goldRect2.x) <= (playerOne.x + playerOne.w) &&
				(goldRect2.y + goldRect2.h) >= (playerOne.y) &&
				(goldRect2.y) <= (playerOne.y + playerOne.h))
			{
				//std::cout << "Gold Bag 2 taken" << std::endl;
				if (renderGold2) {
					puntuacioOne++;
					overallPuntuacion++;
				}
				renderGold2 = false;
			}

			//colision goldRect2 with player 1
			if ((goldRect3.x + goldRect3.w) >= (playerOne.x) &&
				(goldRect3.x) <= (playerOne.x + playerOne.w) &&
				(goldRect3.y + goldRect3.h) >= (playerOne.y) &&
				(goldRect3.y) <= (playerOne.y + playerOne.h))
			{
				//std::cout << "Gold Bag 3 taken" << std::endl;
				if (renderGold3) {
					puntuacioOne++;
					overallPuntuacion++;
				}

				renderGold3 = false;
			}

			//colision goldRect4 with player 1
			if ((goldRect4.x + goldRect4.w) >= (playerOne.x) &&
				(goldRect4.x) <= (playerOne.x + playerOne.w) &&
				(goldRect4.y + goldRect4.h) >= (playerOne.y) &&
				(goldRect4.y) <= (playerOne.y + playerOne.h))
			{
				//std::cout << "Gold Bag 4 taken" << std::endl;
				if (renderGold4) {
					puntuacioOne++;
					overallPuntuacion++;
				}
				renderGold4 = false;
			}

			//colision goldRect5 with player 1
			if ((goldRect5.x + goldRect5.w) >= (playerOne.x) &&
				(goldRect5.x) <= (playerOne.x + playerOne.w) &&
				(goldRect5.y + goldRect5.h) >= (playerOne.y) &&
				(goldRect5.y) <= (playerOne.y + playerOne.h))
			{
				//std::cout << "Gold Bag 5 taken" << std::endl;

				if (renderGold5) {
					puntuacioOne++;
					overallPuntuacion++;
				}

				renderGold5 = false;
			}


			if (overallPuntuacion >= MAXAMOUNT) {
				gamestat = GameState::MENU;
			}


			std::cout << "Puntuacion del player 1 es: " << puntuacioOne<<std::endl;


			/*-------*/
			//DrawPlay();
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, bgTextureBG2, nullptr, &bgRectS2);
			SDL_RenderCopy(renderer, playerTexture, &spriteRectOne, &playerOne);
			SDL_RenderCopy(renderer, playerTexture, &spriteRectTwo, &playerTwo);
			if (renderGold1) SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect1);
			if (renderGold2) SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect2);
			if (renderGold3) SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect3);
			if (renderGold4) SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect4);
			if (renderGold5) SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect5);

			SDL_RenderPresent(renderer);

		case GameState::EXIT:
			break;

		case GameState::MENU:
			//EventHandleMenu();
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					//isRunning = false;
					gamestat = GameState::EXIT;
					break;

				case SDL_MOUSEBUTTONDOWN:
					//std::cout << "Button was pressed at x: " << event.motion.x << " and y: " << event.motion.y << std::endl;
				case SDL_MOUSEMOTION:
					if (event.motion.x > textPlayRect.x && event.motion.x < (textPlayRect.x + textPlayRect.h)
						&& event.motion.y > textPlayRect.y && event.motion.y < (textPlayRect.y + textPlayRect.w / 2))
					{
						//std::cout << "Mouseover play" << std::endl;
						isHoverPlay = true;
					}
					else isHoverPlay = false;
					if (event.motion.x > textStopRect.x && event.motion.x < (textStopRect.x + textStopRect.h)
						&& event.motion.y > textStopRect.y && event.motion.y < (textStopRect.y + textStopRect.w / 2))
					{
						//std::cout << "Mouseover exit" << std::endl;
						isHoverExit = true;
					}
					else isHoverExit = false;

				default:
					break;
				}
			}
			/*-------*/
			//UpdateMenu();
			if (isHoverPlay && event.type == SDL_MOUSEBUTTONDOWN)
			{
				//std::cout << "Change Scene" << std::endl;
				gamestat = GameState::PLAY;
			}
			if (isHoverExit && event.type == SDL_MOUSEBUTTONDOWN)
			{
				//std::cout << "Exit Game" << std::endl;
				gamestat = GameState::EXIT;
				puntuacioOne = 0;
				overallPuntuacion = 0;
				renderGold1 = true;
				renderGold2 = true;
				renderGold3 = true;
				renderGold4 = true;
				renderGold5 = true;
			}



			/*-------*/
			//DrawMenu();
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, bgTextureBG1, nullptr, &bgRectS1);									//RenderBackgrounScene1
			SDL_RenderCopy(renderer, textPlayTexture, nullptr, &textPlayRect);							// RenderPlayText
			if (isHoverPlay) SDL_RenderCopy(renderer, textPlayTexture2, nullptr, &textPlayRect2);		// RenderPlayTextInHover
			SDL_RenderCopy(renderer, textStopTexture, nullptr, &textStopRect);							//RenderStopText
			if (isHoverExit) SDL_RenderCopy(renderer, textStopTexture2, nullptr, &textStopRect2);		//RenderStopTextInHover

			SDL_RenderPresent(renderer);

		default:
			break;
		}
	}

#pragma endregion


#pragma region "Destroy"
	// --- DESTROY ---
	Mix_CloseAudio();
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(bgTextureBG1);
	SDL_DestroyTexture(bgTextureBG2);
	SDL_DestroyTexture(goldTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
#pragma endregion

	// --- QUIT ---
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}
