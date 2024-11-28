#include "colour.h"
#include <SDL.h>


Colour::Colour(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
Colour::~Colour() {}

void Colour::setAs(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Uint32 Colour::mapRGB(SDL_Surface *surface) {
    return SDL_MapRGB(surface->format, r, g, b);
}
Uint32 Colour::mapRGBA(SDL_Surface *surface) {
    return SDL_MapRGBA(surface->format, r, g, b, a);
}

int retMult(int x) {
    return x, x*2, x*3;
}