#pragma once
#include "Game.h"


Game::Game() {

	gmst = GameState::MENU;
	currentScene = new Menu();

}


Game::~Game() {
}

void Game::Run() {

	while (gmst != GameState::EXIT) {

		switch (currentScene->getState()) {

		case SceneState::RUNNING:
			currentScene->EventHandler();
			currentScene->Update();
			currentScene->Draw();
			break;

		case SceneState::GOTO:
			//GOTOSCENE
			switch (gmst) {
			case GameState::PLAY:
				delete currentScene;
				currentScene = new Menu();
				gmst = GameState::MENU;
				

			case GameState::MENU:
				delete currentScene;
				currentScene = new Play();
				gmst = GameState::PLAY;

			case GameState::EXIT:
				gmst = GameState::EXIT;
				delete currentScene;
				
			default:
				break;
			}

			break;

		case SceneState::EXIT:
			//EXIT
			gmst = GameState::EXIT;
			delete currentScene;
			break;

		default:
			break;
		}

	}


}