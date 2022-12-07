#include "math.h"

void printVector2f(const Vector2f vect) {  printf("%f, %f\n", vect.x, vect.y); }

Vector2f vector2f(float x, float y) { Vector2f vect; vect.x = x; vect.y = y; return vect; }