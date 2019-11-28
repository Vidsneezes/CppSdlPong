#pragma once
#include "Pong.h"

class Point
{
public:
	double x;
	double y;

	Point(double _x, double _y);
};

class Sprite
{
public :
	Sprite();
	Sprite(double i_x, double i_y, const char *ptr, SDL_Renderer *ren);
	Sprite(double i_x, double i_y, SDL_Texture *_texture);

	double x;
	double y;
	double width;
	double height;
	double velocityX;
	double velocityY;

	Point *center;

	SDL_Texture *texture;
	void initSize();
	void updateBounds();
	void update(double deltaTime);
	void render(SDL_Renderer *ren);
	void free();

	

private :
	bool destroyTexture;

};



