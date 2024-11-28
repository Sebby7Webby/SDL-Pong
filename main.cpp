#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "classes/classes.h"
#include <iostream>
#include <math.h>
#include "log/log.h"

using namespace std;

void drawBackground(SDL_Renderer *renderer, Colour *colour);
void deltaTimeCalculator(double *delta, Uint64 *last, Uint64 *now);

int main() {
    Log log("main.log", true);

    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 500;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double Delta = 0;

    Colour red(255, 0, 0, 255);
    Colour green(0, 255, 0, 255);
    Colour blue(0, 0, 255, 255);
    Colour black(0, 0, 0, 255);
    Colour white(255, 255, 255, 255);
    Colour pink(252, 15, 192, 255);

    const float SPEED = 0.5;
    float ballSpeed = SPEED/2;

    Vector opponentPaddleVector(0, 0);

    SDL_FRect opponentPaddleRect{WINDOW_WIDTH-60, 250.0f, 10.0f, 100.0f};
    CollisionObject opponentPaddle(&opponentPaddleRect, &green);

    Vector paddleVector(0, 0);
    
    SDL_FRect paddleRect{50.0f, 250.0f, 10.0f, 100.0f};
    CollisionObject paddle(&paddleRect, &blue);

    SDL_FRect ballRect{400.0f, 250.0f, 25.0f, 25.0f};
    CollisionObject ball(&ballRect, &red);
    Vector ballVector(SPEED*cos(45), SPEED*sin(45));
    Vector normalisedBallVector = ballVector.normalise();

    bool running = true;

    while (running) {
        deltaTimeCalculator(&Delta, &LAST, &NOW);

        drawBackground(renderer, &black);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_w:
                            paddleVector.setY(-SPEED);
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            paddleVector.setY(SPEED);
                            break;
                        case SDLK_SPACE:
                            log.logNote("Logged a bookmark here ---------------------------------------------------------------------!");
                        default: break;
                    } break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_w:
                            if (paddleVector.getY() < 0) {
                                paddleVector.setY(0);
                            } break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            if (paddleVector.getY() > 0) {
                                paddleVector.setY(0);
                            } break;
                        default: break;
                    } break;
            }
        } 

        ballVector = normalisedBallVector.multiply(ballSpeed);
        ball.applyVector(ballVector, Delta);
        ball.render(renderer);
        green.setAs(renderer);

        if (abs(ballRect.y - opponentPaddleRect.y) > 0) {
            if (ballRect.y > opponentPaddleRect.y) {
                opponentPaddleVector.setY(SPEED);
            } else {
                opponentPaddleVector.setY(-SPEED);
            }
        } else {
            opponentPaddleVector.setY(0);
        }

        paddle.applyVector(paddleVector, Delta);

        int keepPaddleOffWall = paddle.isOnEdge(WINDOW_WIDTH, WINDOW_HEIGHT);
        paddle.exitEdge(keepPaddleOffWall, WINDOW_WIDTH, WINDOW_HEIGHT);

        paddle.render(renderer);

        opponentPaddle.applyVector(opponentPaddleVector, Delta);

        keepPaddleOffWall = opponentPaddle.isOnEdge(WINDOW_WIDTH, WINDOW_HEIGHT);
        opponentPaddle.exitEdge(keepPaddleOffWall, WINDOW_WIDTH, WINDOW_HEIGHT);

        opponentPaddle.render(renderer);

        int edgeHit = ball.isOnEdge(WINDOW_WIDTH, WINDOW_HEIGHT);
        if (edgeHit != 0) {

            ball.exitEdge(edgeHit, WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        edgeHit = max(edgeHit, paddle.isColliding(ball));
        edgeHit = max(edgeHit, opponentPaddle.isColliding(ball));

        if (edgeHit!=0) {
            ballSpeed*=1.02;
            if (edgeHit <= 2) {
                normalisedBallVector.reverseX();
            } else {
                normalisedBallVector.reverseY();
            }
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

void deltaTimeCalculator(double *delta, Uint64 *last , Uint64 *now) {
    *last = *now;
    *now = SDL_GetPerformanceCounter();

    *delta = (*now-*last)*1000 / (double) SDL_GetPerformanceFrequency();
}

void drawBackground(SDL_Renderer *renderer, Colour *colour) {
    colour->setAs(renderer);
    SDL_RenderClear(renderer);
}