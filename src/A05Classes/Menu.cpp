#pragma once
#include "Menu.h"




Menu::Menu() {

	clicked = false;
	isHoverPlay = false;
	isHoverExit = false;
	//Font font = { PATH_FONT }
	Renderer::Instance()->LoadTexture(MENU_BG, PATH_IMG + "/bg.jpg");
	//Renderer::Instance()->LoadFont();
	scenestate = SceneState::RUNNING;
}


Menu::~Menu() {

}


void Menu::EventHandler() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			
		case SDL_QUIT:
			scenestate = SceneState::EXIT;
			break;

		case SDL_MOUSEBUTTONDOWN:
			clicked = true;
			break;

		case SDL_MOUSEMOTION:
			if (event.motion.x > textPlayRect.x && event.motion.x < (textPlayRect.x + textPlayRect.h)
				&& event.motion.y > textPlayRect.y && event.motion.y < (textPlayRect.y + textPlayRect.w / 2)) {
				isHoverPlay = true;
			}

			else isHoverPlay = false;

			if (event.motion.x > textStopRect.x && event.motion.x < (textStopRect.x + textStopRect.h)
				&& event.motion.y > textStopRect.y && event.motion.y < (textStopRect.y + textStopRect.w / 2)) {
				isHoverExit = true;
			}

			else isHoverExit = false;

			break;

		default:
			clicked = false;
			break;

		}
	}
}


void Menu::Update() {

	if (isHoverExit) {
		//Cambio de color
	}

	if (isHoverPlay) {

		//Cambio de color
	}


	if (isHoverPlay && clicked) {
		std::cout << "Pressed play" << std::endl;
	}

	if (isHoverExit && clicked) {
		std::cout << "Pressed exit" << std::endl;
	}
}


void Menu::Draw() {
	
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(MENU_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	Renderer::Instance()->Render();

}