#pragma once
#include "Scene.h"

class Play : public Scene{
public:
	Play();
	~Play();

	void EventHandler();
	void Update();
	void Draw();
};

