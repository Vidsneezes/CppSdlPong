#include "Sprite.h"

Sprite::Sprite()
{
	x = 0;
	y = 0;
	velocityX = 0;
	velocityY = 0;
	texture = NULL;
	destroyTexture = false;
}

//Creates sprite with a unique texture
Sprite::Sprite(double i_x, double i_y, const char *ptr, SDL_Renderer *ren)
{
	Sprite::Sprite();

	x = i_x;
	y = i_y;

	destroyTexture = true;

	texture = IMG_LoadTexture(ren, ptr);
}

//Use to create a sprite and feed a already loaded texture
Sprite::Sprite(double i_x, double i_y, SDL_Texture *_texture)
{
	Sprite::Sprite();

	x = i_x;
	y = i_y;

	texture = _texture;
}

void Sprite::render(SDL_Renderer *ren)
{
	SDL_Rect textureRect;
	textureRect.x = SDL_floor(x);
	textureRect.y = SDL_floor(y);

	SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
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