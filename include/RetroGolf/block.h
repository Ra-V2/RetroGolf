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

extern Entity* blocks;
extern int blocksSize;

extern SDL_Texture* block64Tex;
extern SDL_Texture* block32Tex;

void initBlocks(Vector2f pos, SDL_Texture* blocksTex, int n);

void reallocBlocks(int n);
void clearBlocks();
void updateBlocks(int level);