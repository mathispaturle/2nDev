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

#define PERCMOVEMENT 10

#define PLAYERWIDTH 350
#define PLAYERHEIGHT 189

#define OFFSET 50

enum class GameState{ PLAY, EXIT, MENU};


//INIT IMG
const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };


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


	#pragma endregion

	#pragma region "Window Region"
	/*
	 *
	 *	--- WINDOW ---
	 *
	 */
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	#pragma endregion

	#pragma region "Renderer Region"
	/*
	 *
	 *	--- RENDERER ---
	 *
	 */

	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	
#pragma endregion
	
	#pragma region "Sprites"
	/*
	 *
	 *	--- SPRITES ---
	 *
	 */

	//Load Textures & Init
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Load player
	//SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/kintoun.png") };
	//if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	//SDL_Rect playerRect{ 0, 0, PLAYERWIDTH, PLAYERHEIGHT };

	//Auxiliar Rect for player movement 
	SDL_Rect playerTarget{ 0, 0, 100, 100 };

	// --- Animated Sprite ---
	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/sp01.png") };
	if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect playerRect, playerPostion;
	int textWidth, textHeight, frameWidth, frameHeight;

	
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);		//Obtener el tamaño de la propia imagen, se pasa por referencia para poder cambiar el valor sin tener que retornara nada
	frameWidth = textWidth / 6;
	frameHeight = textHeight / 1;
	playerPostion.x = playerPostion.y = 0;
	playerRect.x = playerRect.y = 0;
	playerPostion.h = playerRect.h = frameHeight;
	playerPostion.w = playerRect.w = frameWidth;
	int frameTime = 0;

	#pragma endregion

	#pragma region "Text Region"
	/*
	 *
	 *	--- TEXT ---
	 *
	 */
	TTF_Font *font{ TTF_OpenFont("../../GameProject/res/ttf/saiyan.ttf", 80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{255, 150, 0, 255}) };
	if (tmpSurf == nullptr) TTF_CloseFont(font), throw "Unable to create the SDL text surface";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textRect{ 100, 50, tmpSurf->w, tmpSurf->h };
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);


	#pragma endregion

	#pragma region "Audio Region"
	 /*
	 *
	 *	--- AUDIO ---
	 *
	 */

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {	//Check why -1
		throw "Unable to initialize SDL_mixer audio systems";
	}

	Mix_Music *soundtrack{ Mix_LoadMUS("../../GameProject/res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the mix_music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);	//-1 loop infinit
	// Mix_PlayingMusic();
	// Mix_PauseMusic();
	// Mix_PausedMusic();

	//ACTIVITAT, PLAY / STOP MUSIC

	#pragma endregion

	#pragma region "Game Loop Region"
	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	GameState gamestat = GameState::MENU;

	//while (isRunning){

	while (gamestat != GameState::EXIT){

		/*
		switch (gamestat) {

			case GameState::PLAY:
				//EventHandlePlay();
				//UpdatePlay();
				//DrawPlay();

			case GameState::EXIT:
				break;

			case GameState::MENU:
				//EventHandlePlay();
				//UpdatePlay();
				//DrawPlay();
				

			default:
				break;
		}
		*/
	
	#pragma region "Handle Events"
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		
				//isRunning = false; 
				gamestat = GameState::EXIT;
				break;

			case SDL_KEYDOWN:	
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; 
				break;

			case SDL_MOUSEMOTION:
				playerTarget.x = event.motion.x - PLAYERWIDTH/2 + OFFSET; 
				playerTarget.y = event.motion.y - PLAYERHEIGHT/2; 
				break;

			default:;
			}
		}
#pragma endregion

	#pragma region "Update"
		// UPDATE
		frameTime++;

		if (timeDown >= 0) {
			deltaTime = (clock() - lastTime);
			lastTime = clock();
			deltaTime /= CLOCKS_PER_SEC;
			timeDown -= deltaTime;
			std::cout << timeDown << std::endl;
		}

		


		if (FPS / frameTime <= 9) {

			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth) {

				playerRect.x = 0;
			}

		}



		//playerRect.x += (playerTarget.x - playerRect.x) / 10;
		//playerRect.y += (playerTarget.y - playerRect.y) / 10;
		
	#pragma endregion	

	#pragma region "Draw"
		// DRAW
			//Background renderer
			SDL_RenderClear(renderer);

			/*********BG TEXTURE RENDER********/
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);

			/*********PLAYER TEXTURE RENDER********/
			//Static Texture -> NUBE+
			//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);

			//Dynamic Texture -> player
			SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPostion);

			//FONT
			SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);


			//Animated Sprite
			SDL_RenderPresent(renderer);

	#pragma endregion
	
	}

	#pragma endregion

	// --- DESTROY ---
	Mix_CloseAudio();
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// --- QUIT ---
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}