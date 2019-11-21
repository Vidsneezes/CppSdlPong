#include "PlayerPaddle.h"


PlayerPaddle::PlayerPaddle(SDL_Texture *tex)
{
	sprite = new Sprite(40, 20, tex);
}

void PlayerPaddle::destroy()
{
	sprite->free();
	delete sprite;
	sprite = NULL;
}

void PlayerPaddle::update(double deltaTime)
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
	//check input and move player
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		sprite->velocityY = 10;
	}
	else if (currentKeyStates[SDL_SCANCODE_UP])
	{
		sprite->velocityY = -10;
	}
	else
	{
		sprite->velocityY = 0;
	}


	if (sprite->y > lowerLevelLimit)
	{
		sprite->y = lowerLevelLimit;
	}
	else if (sprite->y < upperLevelLimit)
	{
		sprite->y = upperLevelLimit;
	}

	sprite->update(deltaTime);
}

void PlayerPaddle::render(SDL_Renderer *ren)
{
	sprite->render(ren);
}