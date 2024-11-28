#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"
#include "vector.h"
#include "colour.h"

class CollisionObject {
public:
    CollisionObject(SDL_FRect *rect, Colour *colour);
    ~CollisionObject();

    void applyVector(Vector &v, float Delta);
    void render(SDL_Renderer *renderer);
    int isColliding(CollisionObject &body);
    int isOnEdge(int w, int h);
    void exitEdge(int side, int windowWidth, int windowHeight);
private:
    SDL_FRect *rect;
    Colour *colour;
};

#endif