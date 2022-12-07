#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "block.h"

Entity* blocks;
int blocksSize;

SDL_Texture* block64Tex;
SDL_Texture* block32Tex;


void initBlocks(Vector2f pos, SDL_Texture* blocksTex, int n)
{
    blocks = malloc(n * sizeof(Entity));
    blocksSize = n;

    if(blocks == NULL) { printf("ERROR: UNABLE TO ALLOCATE MEMORY!");}

    for(int i = 0; i < n; i++)
    {
        blocks[i] = initEntity(pos, 0.0f, blocksTex);
    }
}

void addBlocks(Vector2f pos, SDL_Texture* blocksTex, int n)
{
    blocks = realloc(blocks, (n+blocksSize) * sizeof(Entity));
    if(blocks == NULL) { printf("ERROR: UNABLE TO REALLOCATE MEMORY!");}

    for(int i = blocksSize; i < n+blocksSize; i++)
    {
        blocks[i] = initEntity(pos, 0.0f, blocksTex);
    }

    blocksSize += n;
}

void clearBlocks()
{
    free(blocks);
    blocksSize = 0;
}

void updateBlocks(int level)
{
    switch(level)
    {
        case 0:
        clearBlocks();
        ball.pos = vector2f(100, 320);
        hole.pos = vector2f(700, 320);

        initBlocks(vector2f(0,0), block64Tex, 2 );

        blocks[0].pos = vector2f(384, 110);
        blocks[1].pos = vector2f(384, 490);
        
        addBlocks(vector2f(0,0), block32Tex, 1 );

        blocks[2].pos = vector2f(398, 315);

        break;

        case 1:
        clearBlocks();

        ball.pos = vector2f(410, 560);
        hole.pos = vector2f(408, 200);

        initBlocks(vector2f(0,0), block64Tex, 3 );

        blocks[0].pos = vector2f(384, 272);
        blocks[1].pos = vector2f(320, 196);
        blocks[2].pos = vector2f(448, 196);

        addBlocks(vector2f(0,0), block32Tex, 2 );

        blocks[3].pos = vector2f(100, 265);
        blocks[4].pos = vector2f(680, 265);

        break;

        case 2:
        clearBlocks();

        ball.pos = vector2f(680, 540);
        hole.pos = vector2f(130, 100);

        initBlocks(vector2f(0,0), block32Tex, 10 );

        blocks[0].pos = vector2f(280, 42);
        blocks[1].pos = vector2f(280, 110);
        blocks[2].pos = vector2f(280, 178);
        blocks[3].pos = vector2f(280, 246);
        blocks[4].pos = vector2f(280, 314);

        blocks[5].pos = vector2f(488, 292);
        blocks[6].pos = vector2f(488, 360);
        blocks[7].pos = vector2f(488, 428);
        blocks[8].pos = vector2f(488, 496);
        blocks[9].pos = vector2f(488, 564);


        break;

        case 3:
        clearBlocks();
        
        ball.pos = vector2f(110, 530);
        hole.pos = vector2f(392, 270);

        initBlocks(vector2f(0,0), block32Tex, 2 );

        blocks[0].pos = vector2f(320, 256);
        blocks[1].pos = vector2f(448, 256);

        addBlocks(vector2f(0,0), block64Tex, 4);

        blocks[2].pos = vector2f(320, 320);
        blocks[3].pos = vector2f(416, 320);

        blocks[4].pos = vector2f(96, 96);
        blocks[5].pos = vector2f(640, 480);

        addBlocks(vector2f(0,0), block32Tex, 3);

        blocks[6].pos = vector2f(320, 192);
        blocks[7].pos = vector2f(448, 192);
        blocks[8].pos = vector2f(384, 192);

        break;

        case 4:
        clearBlocks();

        ball.pos = vector2f(392, 100);
        hole.pos = vector2f(392, 550);

        initBlocks(vector2f(0,0), block64Tex, 3 );

        blocks[0].pos = vector2f(300, 100);
        blocks[1].pos = vector2f(434, 100);
        blocks[2].pos = vector2f(368, 216);

        addBlocks(vector2f(0,0), block32Tex, 2 );
        blocks[3].pos = vector2f(358, 500);
        blocks[4].pos = vector2f(412, 500);

        break;

        default:
        break;
    }
}