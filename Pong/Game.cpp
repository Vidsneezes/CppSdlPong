#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Screen dimensions

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer * ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *backgroundPng = NULL;

	int posX = 100, posY = 100, width = 480, height = 320;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Hello world", posX, posY, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
	
	//load textures
	backgroundPng = loadTexture("res/background.png", renderer);

	while (1)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				break;
			}
		}

		SDL_RenderClear(renderer);
		renderTexture(backgroundPng, renderer, 0, 0);
		SDL_RenderPresent(renderer);
	}


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	//Clean up
	SDL_DestroyTexture(backgroundPng);
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

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect textureRect;
	textureRect.x = x;
	textureRect.y = y;

	SDL_QueryTexture(tex, NULL, NULL, &textureRect.w, &textureRect.h);
	SDL_RenderCopy(ren, tex, NULL, &textureRect);
}

