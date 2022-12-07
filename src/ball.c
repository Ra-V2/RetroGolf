#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdlib.h>

#include "ball.h"

Entity ball;
Entity arrow;

BallValues ballValues;

SDL_Texture* ballTex;
SDL_Texture* arrowTex;

Mix_Chunk* strikeSfx;
Mix_Chunk* holeSfx;

int strokes = 0;
bool levelCompleted = false;

void initBall(Vector2f pos, SDL_Texture* ballTex, SDL_Texture* arrowTex)
{
    ball = initEntity(pos, 0.0f, ballTex);
    arrow = initEntity(vector2f(-64, -64), 0.0f, arrowTex);

    ballValues.dirX = 1;
    ballValues.dirY = 1;

    ballValues.moveAvailable = true;
    ballValues.inHole = false;
    ballValues.mouseOnBall = false;
    ballValues.sfxPlayed = true;
    ballValues.friction = 0.012;

    strikeSfx = Mix_LoadWAV("res/sfx/strike.wav");
    holeSfx = Mix_LoadWAV("res/sfx/hole.wav");
}

void setBallVel(float x, float y)
{
    ballValues.velocity.x = x;
    ballValues.velocity.y = y;
}

void setBallLaunchVel(float x, float y)
{
    ballValues.launchedVelocity.x = x;
    ballValues.launchedVelocity.y = y;
}

void setBallInitMousePos(float x, float y)
{
    ballValues.initialMousePos.x = x;
    ballValues.initialMousePos.y = y;
}


void updateBall(double deltaTime, bool mouseDown, bool mousePressed)
{

    //the ball flew into the hole
    if (ballValues.inHole)
    {
        if (ball.pos.x < hole.pos.x)
        {
            setPosEn(&ball, ball.pos.x += deltaTime, ball.pos.y);
        }
        else if (ball.pos.x > hole.pos.x)
        {
            setPosEn(&ball, ball.pos.x -= deltaTime, ball.pos.y);
        }
        if (ball.pos.y < hole.pos.y)
        {
            setPosEn(&ball, ball.pos.x, ball.pos.y += deltaTime);
        }
        else if (ball.pos.y > hole.pos.y)
        {
            setPosEn(&ball, ball.pos.x, ball.pos.y -= deltaTime);
        }
        setScaleEn(&ball, ball.scale.x - 0.05*deltaTime, ball.scale.y - 0.05*deltaTime);

        if(ball.scale.x <= 0.05) {
            levelCompleted = true;
            ballValues.inHole = false;
            ball.scale = vector2f(1.0f, 1.0f);
            ballValues.velocity1D = 0;
        }

        return;
    }

    //check mouse position
    if(mousePressed)
    {
        int mX = 0;
        int mY = 0;

        SDL_GetMouseState(&mX, &mY);

        if(mX >= ball.pos.x-8 && mY >= ball.pos.y-8 && mX <= ball.pos.x+20 && mY <= ball.pos.y+20)
            ballValues.mouseOnBall = true;
        else
            ballValues.mouseOnBall = false;
            
    }

    //calculate ball movement vector
    if(mousePressed && ballValues.moveAvailable && ballValues.mouseOnBall)
    {
        int mX = 0;
        int mY = 0;

        SDL_GetMouseState(&mX, &mY);

        ballValues.initialMousePos.x = mX;
        ballValues.initialMousePos.y = mY;
        
        arrow.angle = SDL_atan2(-mX, -mY);
    }

    if(mouseDown && ballValues.moveAvailable && ballValues.mouseOnBall)
    {
        int mX = 0;
        int mY = 0;

	SDL_GetMouseState(&mX, &mY);

        setBallVel((mX - ballValues.initialMousePos.x), (mY - ballValues.initialMousePos.y));
        setBallLaunchVel((mX - ballValues.initialMousePos.x), (mY - ballValues.initialMousePos.y));

        ballValues.velocity1D = SDL_sqrt(SDL_pow(abs(ballValues.velocity.x), 2) + SDL_pow(abs(ballValues.velocity.y), 2));
        ballValues.launchedVelocity1D = ballValues.velocity1D;

        ballValues.dirX = -ballValues.velocity.x/abs(ballValues.velocity.x);
        ballValues.dirY = -ballValues.velocity.y/abs(ballValues.velocity.y);

        if (ballValues.velocity1D > 1)
        {
            ballValues.velocity1D = 1;
            ballValues.launchedVelocity1D = 1;
        }

        arrow.pos = vector2f(ball.pos.x, ball.pos.y - 24);
        arrow.angle = SDL_atan2(-ballValues.velocity.y, -ballValues.velocity.x)*(float)(180/3.1415)+90.0f;

        ballValues.sfxPlayed = false;
    } else
    {
        if(!ballValues.sfxPlayed)
        {
            Mix_PlayChannel(-1, strikeSfx, 0);
            ballValues.sfxPlayed = true;
            strokes++;
        }
        
        arrow.pos = vector2f(-64, -64);
        arrow.angle = 0.0f;

        setPosEn(&ball, ball.pos.x + ballValues.velocity.x*deltaTime/15, ball.pos.y + ballValues.velocity.y*deltaTime/15);
        if (ballValues.velocity.x > 0.0001 || ballValues.velocity.x < -0.0001 || ballValues.velocity.y > 0.0001 || ballValues.velocity.y < -0.0001)
        {
            if (ballValues.velocity1D > 0)
            {
                ballValues.velocity1D -= ballValues.friction*deltaTime;
            }
            else
            {
                ballValues.velocity1D = 0;
            }

            ballValues.velocity.x = (ballValues.velocity1D/ballValues.launchedVelocity1D)*abs(ballValues.launchedVelocity.x)*ballValues.dirX;
            ballValues.velocity.y = (ballValues.velocity1D/ballValues.launchedVelocity1D)*abs(ballValues.launchedVelocity.y)*ballValues.dirY;

            ballValues.moveAvailable = false;
        }
        else
        {
            setBallVel(0,0);

            int mX = 0;
	    int mY = 0;
            SDL_GetMouseState(&mX, &mY);
            setBallInitMousePos(mX, mY);

            ballValues.moveAvailable = true;
        }

        //check block collision
        for (int i = 0; i < blocksSize; i++)
	    { 
	    
	    float newX = ball.pos.x + ballValues.velocity.x*deltaTime/10;
            float newY = ball.pos.y;

            if (newX + 16 > blocks[i].pos.x && newX < blocks[i].pos.x + blocks[i].currentFrame.w && newY + 16 > blocks[i].pos.y && newY < blocks[i].pos.y + blocks[i].currentFrame.h - 3)
            {
                ballValues.velocity.x = ballValues.velocity.x*-1;
                ballValues.dirX *= -1;
            }

            newX = ball.pos.x;
            newY = ball.pos.y + ballValues.velocity.y*deltaTime/10;

            if (newX + 16 > blocks[i].pos.x && newX < blocks[i].pos.x + blocks[i].currentFrame.w && newY + 16 > blocks[i].pos.y && newY < blocks[i].pos.y + blocks[i].currentFrame.h - 3)
            {
                ballValues.velocity.y = ballValues.velocity.y*-1;
                ballValues.dirY *= -1;
            }
	    }

        //check wall collision
        if (ball.pos.x + ball.currentFrame.w > 768)
        {
            setBallVel(-abs(ballValues.velocity.x), ballValues.velocity.y);
            ballValues.dirX = -1;
        }
        else if (ball.pos.x < 32)
        {
            setBallVel(abs(ballValues.velocity.x), ballValues.velocity.y);
            ballValues.dirX = 1;
        }
        else if (ball.pos.y + ball.currentFrame.h > 608)
        {
            setBallVel(ballValues.velocity.x, -abs(ballValues.velocity.y));
            ballValues.dirY = -1;
        }
        else if (ball.pos.y < 32)
        {
            setBallVel(ballValues.velocity.x, abs(ballValues.velocity.y));
            ballValues.dirY = 1;
        }

        //check hole collision
        if(abs(ballValues.velocity.x) <= 80 && abs(ballValues.velocity.y) <= 80)
        {
            if(ball.pos.x >= hole.pos.x-8 && ball.pos.y >= hole.pos.y-8)
            {
                if(ball.pos.x <= hole.pos.x+16 && ball.pos.y <= hole.pos.y+16)
                    {
                        ballValues.inHole = true;
                        Mix_PlayChannel(-1, holeSfx, 0);
                    }
            }
        }
    }

}
