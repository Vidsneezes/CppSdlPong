#pragma once
#include "Sprite.h"

class PlayerPaddle {
public:
	PlayerPaddle(SDL_Texture *tex);
	Sprite *sprite;
	const int upperLevelLimit = 20;
	const int lowerLevelLimit = 320 - 78 - 20; // window height - paddle image height - pad
	void update(double deltaTime);
	void destroy();
	void render(SDL_Renderer *ren);
};