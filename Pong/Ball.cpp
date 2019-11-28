#include "Ball.h"

Ball::Ball(SDL_Texture *tex)
{
	sprite = new Sprite(worldMaxX / 2, worldMaxY /2, tex);
}

void Ball::destroy()
{
	sprite->free();
	delete sprite;
	sprite = NULL;
}

void Ball::SetSpeed(int _spdX, int _spdY)
{
	speedX = _spdX;
	speedY = _spdY;

	if (sprite != NULL)
	{
		sprite->velocityX = speedX;
		sprite->velocityY = speedY;
	}
}

void Ball::render(SDL_Renderer *ren)
{
	sprite->render(ren);
}

void Ball::update(double deltaTime)
{
	sprite->update(deltaTime);

	sprite->updateBounds();

	Point *_center = sprite->center;

	if (_center->x > worldMaxX)
	{
		sprite->velocityX = -speedX;
	}
	else if (_center->x < worldMinX)
	{
		sprite->velocityX = speedX;
	}

	if (_center->y > worldMaxY)
	{
		sprite->velocityY = -speedY;
	}
	else if (_center->y < worldMinY)
	{
		sprite->velocityY = speedY;
	}
}