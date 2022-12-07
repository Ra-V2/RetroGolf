#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "entity.h"

void renderWindow(const char * windowTitle, int windowWidth, int windowHeight);
SDL_Texture* loadTexture(const char* filePath);

void displayRender();
void clearRender();

void renderTexture(int x, int y, SDL_Texture* texture);

void renderEntity(Entity* en);
void renderEntityEx(Entity* en);

void renderText(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor);
void renderTextCenter(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor);

extern SDL_Window* window;
extern SDL_Renderer* renderer;
