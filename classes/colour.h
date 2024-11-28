#ifndef COLOUR_H
#define COLOUR_H

#include <SDL.h>

class Colour {
public:
    Colour(int r, int g, int b, int a);
    ~Colour();

    void setAs(SDL_Renderer *renderer);
    Uint32 mapRGB(SDL_Surface *surface);
    Uint32 mapRGBA(SDL_Surface *surface);
private:
    int r, g, b, a;
};

#endif