#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "entity.h"

Entity initEntity(Vector2f pos, float angle, SDL_Texture* tex)
{
    Entity entity;

    entity.pos = pos;
    entity.tex = tex;
    entity.angle = angle;
    entity.scale.x = 1.0f;
    entity.scale.y = 1.0f;

    entity.currentFrame.x = 0;
    entity.currentFrame.y = 0;
    entity.currentFrame.w = 32;
    entity.currentFrame.h = 32;

    SDL_QueryTexture(tex, NULL, NULL, &entity.currentFrame.w, &entity.currentFrame.h);

    return entity;
}

void setPosEn(Entity* en, float x, float y)
{
    en->pos.x = x;
    en->pos.y = y;
}

void setScaleEn(Entity* en, float w, float h)
{
    en->scale.x = w;
    en->scale.y = h;
}

void setAngleEn(Entity* en, float angle)
{
    en->angle = angle;
}

SDL_Texture* getTexEn(Entity* en)
{
    return en->tex;
}

SDL_Rect getCurrentFrame(Entity* en)
{
    return en->currentFrame;
}



