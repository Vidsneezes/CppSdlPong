#include "Sprite.h"

Sprite::Sprite()
{
	x = 0;
	y = 0;
	texture = NULL;
}

//Creates sprite with a unique texture
Sprite::Sprite(double i_x, double i_y, const char *ptr, SDL_Renderer *ren)
{
	x = i_x;
	y = i_y;

	texture = IMG_LoadTexture(ren, ptr);
}

//Use to create a sprite and feed a already loaded texture
Sprite::Sprite(double i_x, double i_y, SDL_Texture *_texture)
{
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
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}