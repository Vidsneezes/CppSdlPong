#include "Pong.h"
#include "Sprite.h"

//Screen dimensions

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer * ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, double x, double y);

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;


	SDL_Texture *paddleTexture = NULL;
	SDL_Texture *ballTexture = NULL;

	int posX = 100, posY = 100, width = 480, height = 320;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Hello world", posX, posY, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
	
	//Load textures
	paddleTexture = loadTexture("res/paddle.png", renderer);

	//Create Sprites
	Sprite backgroundSprite(0, 0, "res/background.png", renderer);
	Sprite player_1(40, 20, paddleTexture);
	Sprite computer_1(480 - 40 - 27, 20, paddleTexture);
	Sprite ball(480 / 2, 320 / 2, "res/ball.png", renderer);

	ball.velocityX = 30.0;
	ball.velocityY = 25.0;

	bool quit = false;
	SDL_Event e;

	Uint32 lastTick = SDL_GetTicks();

	double deltaTime = 0;

	int upperLevelLimit = 20;
	int lowerLevelLimit = 320 - 78 - 20; // window height - paddle image height - pad

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		deltaTime = (SDL_GetTicks() - lastTick) / 100.0;

		//Logic
		const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
		
		//check input and move player
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			player_1.velocityY = 10;
		}
		else if (currentKeyStates[SDL_SCANCODE_UP])
		{
			player_1.velocityY = -10;
		}


		//updates
		player_1.update(deltaTime);
		computer_1.update(deltaTime);
		ball.update(deltaTime);

		//limit player movement 
		if (player_1.y > lowerLevelLimit)
		{
			player_1.y = lowerLevelLimit;
		}
		else if (player_1.y < upperLevelLimit)
		{
			player_1.y = upperLevelLimit;
		}


		//Reset ticks
		lastTick = SDL_GetTicks();

		// Render
		SDL_RenderClear(renderer);
		backgroundSprite.render(renderer);
		player_1.render(renderer);
		computer_1.render(renderer);
		ball.render(renderer);

		SDL_RenderPresent(renderer);
	}

	//Clean up
	//Free sprite texture
	backgroundSprite.free();
	ball.free();
	//Destroy textures
	SDL_DestroyTexture(paddleTexture);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Exit
	SDL_Quit();
	return EXIT_SUCCESS;
}

SDL_Texture* loadTexture(const std::string &file,SDL_Renderer * ren)
{
	return IMG_LoadTexture(ren, file.c_str());
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, double x, double y)
{
	SDL_Rect textureRect;
	textureRect.x = (double)SDL_floor(x);
	textureRect.y = (double)SDL_floor(y);

	SDL_QueryTexture(tex, NULL, NULL, &textureRect.w, &textureRect.h);
	SDL_RenderCopy(ren, tex, NULL, &textureRect);
}

