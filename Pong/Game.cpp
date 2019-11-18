#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Screen dimensions

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer * ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, double x, double y);

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *backgroundTexture = NULL;
	SDL_Texture *paddleTexture = NULL;
	SDL_Texture *ballTexture = NULL;

	int posX = 100, posY = 100, width = 480, height = 320;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Hello world", posX, posY, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
	
	//load textures
	backgroundTexture = loadTexture("res/background.png", renderer);
	paddleTexture = loadTexture("res/paddle.png", renderer);
	ballTexture = loadTexture("res/ball.png", renderer);

	bool quit = false;
	SDL_Event e;

	double playerY = 0;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;


	double ballVelX = 60;
	double ballVelY = 40;
	double ballX = 480/2, ballY = 320/2;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceCounter()) * 10000;
		
		//printf("%f",deltaTime);


		//Logic
		const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			playerY += deltaTime * 100;
		}
		else if (currentKeyStates[SDL_SCANCODE_UP])
		{
			playerY -= deltaTime * 100;
		}
		ballX += ballVelX * deltaTime;
		ballY += ballVelY * deltaTime;

		// Render
		SDL_RenderClear(renderer);
		renderTexture(backgroundTexture, renderer, 0, 0);
		renderTexture(paddleTexture, renderer, 40, playerY);
		renderTexture(paddleTexture, renderer, 480-40-27, 20);
		renderTexture(ballTexture, renderer, ballX, ballY);
		SDL_RenderPresent(renderer);
	}


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	//Clean up
	SDL_DestroyTexture(backgroundTexture);
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
	textureRect.x = SDL_floor(x);
	textureRect.y = SDL_floor(y);

	SDL_QueryTexture(tex, NULL, NULL, &textureRect.w, &textureRect.h);
	SDL_RenderCopy(ren, tex, NULL, &textureRect);
}

