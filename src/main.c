#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "render.h"
#include "entity.h"
#include "ball.h"
#include "hole.h"

const int WIDTH = 800, HEIGHT = 640;

int state = 0;
double deltaTime = 0;

Uint64 currentTick;
Uint64 lastTick = 0;

bool mousePressed = 0;
bool mouseDown = 0;
int level = 0;

SDL_Event event;
SDL_Texture* bgTex;
SDL_Texture* logoTex;
SDL_Texture* scoreTex;

TTF_Font* font32;
TTF_Font* font20;

SDL_Color black = { 0, 0, 0 };
SDL_Color white = { 255, 255, 255 };
SDL_Color green = { 82, 127, 57};

bool gameRunning = true;

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();

	deltaTime = (double)((currentTick-lastTick)*100 / (double)SDL_GetPerformanceFrequency());

	mousePressed = false;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}


	updateBall(deltaTime, mouseDown, mousePressed);

	if(levelCompleted)
	{
		level++;
		updateBlocks(level);
		levelCompleted = false;

		if(level == 5)
			state++;
	}
}

void draw()
{
	clearRender();
    renderTexture(0, 0, bgTex);

	char strokesNum[4];
	sprintf( strokesNum, "%d", strokes );

	char strokesText[20] = "SCORE: ";
	strcat(strokesText, strokesNum);

	renderText(42, 578, strokesText, font20, green);
	renderText(42, 577, strokesText, font20, green);
	renderText(42, 576, strokesText, font20, green);
	renderText(42, 575, strokesText, font20, black);

	char levelNum[2];
	sprintf( levelNum, "%d", level+1 );

	char levelText[20] = "LEVEL: ";
	strcat(levelText, levelNum);

	renderText(678, 578, levelText, font20, green);
	renderText(678, 577, levelText, font20, green);
	renderText(678, 576, levelText, font20, green);
	renderText(678, 575, levelText, font20, black);

	for(int i = 0; i < blocksSize; i++)
	{
		renderEntity(&blocks[i]);
	}

	renderEntity(&hole);
	renderEntity(&ball);
	renderEntityEx(&arrow);

	displayRender();
}

void titleScreen()
{
    while(state == 0 && gameRunning != 0)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mousePressed = true;
					state++;
				}
				break;
			}
		}

		clearRender();
    	renderTexture(0, 0, bgTex);

		renderTexture(180, 140 + 4*SDL_sin(SDL_GetTicks()*(3.14/1200)), logoTex);
		
		renderTextCenter(0, 42, "CLICK TO START", font32, green);
		renderTextCenter(0, 43, "CLICK TO START", font32, green);
		renderTextCenter(0, 44, "CLICK TO START", font32, green);
		renderTextCenter(0, 40, "CLICK TO START", font32, black);

		displayRender();
	}
	updateBlocks(level);
}

void endScreen()
{
    while(state == 2 && gameRunning != 0)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mousePressed = true;
					state++;
				}
				break;
			}
		}

		clearRender();
    	renderTexture(0, 0, bgTex);

		renderTexture(175, 140 + 4*SDL_sin(SDL_GetTicks()*(3.14/1200)), scoreTex);

		char strokesNum[4];
		sprintf( strokesNum, "%d", strokes );

		char strokesText[20] = "YOUR SCORE: ";
		strcat(strokesText, strokesNum);
		
		renderTextCenter(0, 42, strokesText, font32, green);
		renderTextCenter(0, 43, strokesText, font32, green);
		renderTextCenter(0, 44, strokesText, font32, green);
		renderTextCenter(0, 40, strokesText, font32, black);

		displayRender();
	}
}

int main( int argc, char *argv[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Event windowEvent;

    renderWindow("RetroGolf", WIDTH, HEIGHT);

    ballTex = loadTexture("res/gfx/ball.png");
    arrowTex = loadTexture("res/gfx/arrow.png");
	block64Tex = loadTexture("res/gfx/box64.png");
	block32Tex = loadTexture("res/gfx/box32.png");
    bgTex = loadTexture("res/gfx/bg.png");
	holeTex = loadTexture("res/gfx/hole.png");
	logoTex = loadTexture("res/gfx/logo.png");
	scoreTex = loadTexture("res/gfx/score.png");

	font32 = TTF_OpenFont("res/font/font.ttf", 32);
	font20 = TTF_OpenFont("res/font/font.ttf", 20);

    initBall(vector2f(500,200), ballTex, arrowTex);
	initHole(vector2f(180,180), holeTex);
	initBlocks(vector2f(0,0), block32Tex, 0);


    while (gameRunning)
    {
		switch(state)
		{
		case 0:
            titleScreen();
			break;
		case 1:
            update();
            draw();
			break;
		case 2:
			endScreen();
			break;
		default:
			gameRunning = false;
		}
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
	TTF_CloseFont(font32);
	TTF_CloseFont(font20);
    TTF_Quit();

    return 0;
}
