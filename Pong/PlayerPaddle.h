#pragma once
#include "Pong.h"
#include "Sprite.h"

class PlayerPaddle {
public:
	PlayerPaddle(SDL_Texture *tex);
	Sprite *sprite;
	void update(double deltaTime);
	void destroy();
	void render(SDL_Renderer *ren);
};