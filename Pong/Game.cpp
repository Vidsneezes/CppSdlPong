#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

//Screen dimensions

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *bitmapTex = NULL;

	int posX = 100, posY = 100, width = 480, height = 320;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Hello world", posX, posY, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
	bitmapTex = IMG_LoadTexture(renderer, "res/sampleImage.png");

	while (1)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_DestroyTexture(bitmapTex);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}