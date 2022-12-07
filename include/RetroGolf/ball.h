#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "entity.h"
#include "ball.h"
#include "math.h"
#include "block.h"
#include "hole.h"


extern Entity ball;
extern Entity arrow;

extern SDL_Texture* ballTex;
extern SDL_Texture* arrowTex;

extern Mix_Chunk* strikeSfx;
extern Mix_Chunk* holeSfx;

extern int strokes;
extern bool levelCompleted;


typedef struct BallValues
{
	Vector2f velocity;
	Vector2f launchedVelocity;
	Vector2f initialMousePos;

	float velocity1D;
	float launchedVelocity1D;
	float friction;

	bool moveAvailable;
	bool inHole;
	bool mouseOnBall;
	bool sfxPlayed;

	int dirX;
	int dirY;
	
} BallValues;

void initBall(Vector2f pos, SDL_Texture* ballTex, SDL_Texture* arrowTex);

void setBallVel(float x, float y);
void setBallLaunchVel(float x, float y);
void setBallInitMousePos(float x, float y);
void setBallWin(bool win);

void updateBall(double deltaTime, bool mouseDown, bool mousePressed);
