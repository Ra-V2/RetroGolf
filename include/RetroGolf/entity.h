#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "math.h"

typedef struct Entity {
    	Vector2f pos;
        float angle;
        Vector2f scale;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
} Entity;

Entity initEntity(Vector2f pos, float angle, SDL_Texture* tex);

void setPosEn(Entity * en, float x, float y);
void setScaleEn(Entity * en, float w, float h);
void setAngleEn(Entity * en, float angle);
void updateEn(Entity * en, double deltaTime);
