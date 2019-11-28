#pragma once
#include "Pong.h"
#include "Sprite.h"

class Ball {
public :
	Ball(SDL_Texture *tex);
	Sprite *sprite;

	//Define the ball bounce perimeter
	const int worldMinX = 0;
	const int worldMaxX = 480;
	const int worldMinY = 0;
	const int worldMaxY = 320;

	int speedX = 0;
	int speedY = 0;

	void update(double deltaTime);
	void destroy();
	void render(SDL_Renderer *ren);
	void SetSpeed(int _spdX, int _spdY);
};