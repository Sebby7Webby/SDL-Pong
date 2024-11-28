#include "collision.h"

CollisionObject::CollisionObject(SDL_FRect *_rect, Colour *colour) 
    : rect(_rect), colour(colour) {}

CollisionObject::~CollisionObject() {}

void CollisionObject::render(SDL_Renderer *renderer) {
    colour->setAs(renderer);
    SDL_RenderFillRectF(renderer, rect);
}

int CollisionObject::isColliding(CollisionObject &body) {
    float yPoints[2] = {body.rect->y, (body.rect->y)+(body.rect->h)};
    float xPoints[2] = {body.rect->x, (body.rect->x)+(body.rect->w)};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if ((xPoints[i] <= (rect->x+rect->w) && xPoints[i] >= rect->x) && (yPoints[j] <= (rect->y+rect->h) && yPoints[j] >= (rect->y))) {
                if (i == 0 && j == 0) {
                    if (xPoints[1-i] > rect->x+rect->w-2 && xPoints[i] > rect->x+rect->w-2) {
                        return 2;
                    } else {
                        return 4;
                    }
                } else if (i == 1 && j == 0) {
                    if (yPoints[1-j] > rect->y+rect->h-2 && yPoints[j] > rect->y+rect->h-2) {
                        return 4;
                    } else {
                        return 1;
                    }
                } else if (i == 1 && j == 1) {
                    if (xPoints[1-i] < rect->x+2 && xPoints[i] < rect->x+2) {
                        return 1;
                    } else {
                        return 3;
                    }
                } else {
                    if (yPoints[1-j] < rect->y+2 && yPoints[j] < rect->y+2) {
                        return 3;
                    } else {
                        return 2;
                    }
                }
            }
        }
    }
    return false;
}

void CollisionObject::applyVector(Vector &v, float Delta) {
    rect->x += v.getX() * Delta;
    rect->y += v.getY() * Delta;
}
int CollisionObject::isOnEdge(int w, int h) {
    if (rect->x <= 0) {
        return 1;
    } if (rect->x+rect->w >= w) {
        return 2;
    } if (rect->y <= 0) {
        return 3;
    } if ((rect->y+rect->h) >= h) {
        return 4;
    }

    return 0;
}

void CollisionObject::exitEdge(int side, int windowWidth, int windowHeight) {
    if (side == 1) {
        rect->x=1;
    } else if (side == 2) {
        rect->x=windowWidth-1-rect->w;
    } else if (side == 3) {
        rect->y=1;
    } else if (side == 4) {
        rect->y=windowHeight-1-rect->h;
    }
}