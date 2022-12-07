#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "entity.h"
#include "ball.h"
#include "math.h"
#include "block.h"

extern Entity hole;
extern SDL_Texture* holeTex;

void initHole(Vector2f pos, SDL_Texture* tex);
void setHolePosition(int x, int y);