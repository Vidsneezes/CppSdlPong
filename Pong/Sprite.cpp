#include "Sprite.h"

Sprite::Sprite()
{
	x = 0;
	y = 0;
	velocityX = 0;
	velocityY = 0;
	texture = NULL;
	destroyTexture = false;
	center = new Point(0, 0);

}

//Creates sprite with a unique texture
Sprite::Sprite(double i_x, double i_y, const char *ptr, SDL_Renderer *ren)
{
	Sprite::Sprite();

	x = i_x;
	y = i_y;

	destroyTexture = true;

	texture = IMG_LoadTexture(ren, ptr);
	initSize();

}

//Use to create a sprite and feed a already loaded texture
Sprite::Sprite(double i_x, double i_y, SDL_Texture *_texture)
{
	Sprite::Sprite();

	x = i_x;
	y = i_y;

	texture = _texture;

	initSize();
}

void Sprite::initSize()
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	width = w;
	height = h;

	center = new Point(0, 0);
	updateBounds();
}

void Sprite::render(SDL_Renderer *ren)
{
	SDL_Rect textureRect;
	textureRect.x = SDL_floor(x);
	textureRect.y = SDL_floor(y);
	textureRect.w = width;
	textureRect.h = height;

	SDL_RenderCopy(ren, texture, NULL, &textureRect);
}

void Sprite::free()
{
	if (destroyTexture)
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
		}
	}
}

void Sprite::update(double deltaTime)
{
	x += (velocityX * deltaTime);
	y += (velocityY * deltaTime);
}

void Sprite::updateBounds()
{
	center->x = x + (width / 2.0f);
	center->y = y + (height / 2.0f);
}

Point::Point(double _x, double _y)
{
	x = _x;
	y = _y;
}