#pragma once

#include <stdio.h>

typedef struct Vector2f
{
    float x, y;
} Vector2f;

void printVector2f(const Vector2f);

Vector2f vector2f(float x, float y);