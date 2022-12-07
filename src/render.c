#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "render.h"

SDL_Window* window;
SDL_Renderer* renderer;

void renderWindow(const char* windowTitle, int windowWidth, int windowHeight)
{
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );

    if(window == NULL)
    {
        printf("Window failed to init. Error: ");
        printf(SDL_GetError());
        printf("\n");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* icon = IMG_Load("res/gfx/icon.png");
    SDL_SetWindowIcon(window, icon);
}

SDL_Texture* loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
    {
		printf("Failed to load texture. Error: ");
        printf(SDL_GetError());
        printf("\n");
    }

	return texture;
}

void renderTexture(int x, int y, SDL_Texture* texture)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w;
    src.h;
    
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void renderEntityEx(Entity* en)
{
    SDL_Rect src;

    src.x = en->currentFrame.x;
    src.y = en->currentFrame.y;
    src.w = en->currentFrame.w;
    src.h = en->currentFrame.h;

    SDL_Rect dst;
    dst.x = en->pos.x;
    dst.y = en->pos.y;
    dst.w = en->currentFrame.w;
    dst.h = en->currentFrame.h;

    SDL_RendererFlip fl;

	SDL_RenderCopyEx(renderer, en->tex, &src, &dst, en->angle, NULL, fl);
}

void renderEntity(Entity* en)
{
    SDL_Rect src;

    src.x = en->currentFrame.x;
    src.y = en->currentFrame.y;
    src.w = en->currentFrame.w;
    src.h = en->currentFrame.h;

    SDL_Rect dst;
    dst.x = en->pos.x + (en->currentFrame.w - en->currentFrame.w * en->scale.x)/2;
    dst.y = en->pos.y + (en->currentFrame.h - en->currentFrame.h * en->scale.y)/2;
    dst.w = en->currentFrame.w * en->scale.x;
    dst.h = en->currentFrame.h * en->scale.y;

	SDL_RenderCopy(renderer, en->tex, &src, &dst);
}

void displayRender()
{
	SDL_RenderPresent(renderer);
}

void clearRender()
{
	SDL_RenderClear(renderer);
}

void renderText(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor)
{
    	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
        src.w = surfaceMessage->w;
        src.h = surfaceMessage->h;


		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}

void renderTextCenter(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor)
{
    	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
        src.w = surfaceMessage->w;
        src.h = surfaceMessage->h;


		SDL_Rect dst;
		dst.x = 800/2 - src.w/2 + x;
		dst.y = 640/2 - src.h/2 + y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}
