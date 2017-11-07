#pragma once
#include "Types.h"
#include "Scene.h"
#include "Renderer.h"
#include "Constants.h"
#include <iostream>



class Menu : public Scene {

private:
	Vector2 pos;
	int score;
	bool clicked;
	bool isHoverPlay;
	bool isHoverExit;

	SDL_Rect textPlayRect, textStopRect;
	

	
public:
	Menu();
	~Menu();

	void EventHandler();
	void Update();
	void Draw();



};

