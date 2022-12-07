#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "hole.h"

Entity hole;
SDL_Texture* holeTex;

void initHole(Vector2f pos, SDL_Texture* tex)
{
    hole = initEntity(pos, 0.0f, tex);
}

void setHolePosition(int x, int y)
{
    hole.pos = vector2f(x, y);
}