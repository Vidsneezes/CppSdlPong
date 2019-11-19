#pragma once
#include "Pong.h"

class Sprite
{
public :
	Sprite();
	Sprite(double i_x, double i_y, const char *ptr, SDL_Renderer *ren);
	Sprite(double i_x, double i_y, SDL_Texture *_texture);

	double x;
	double y;
	double velocityX;
	double velocityY;

	SDL_Texture *texture;
	void update(double deltaTime);
	void render(SDL_Renderer *ren);
	void free();

};