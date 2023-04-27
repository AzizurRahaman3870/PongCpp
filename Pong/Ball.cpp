#include "Ball.h"

Ball::Ball()
{
    ball.w = 10;
    ball.h = 10;
    ball.x = 640/2 - ball.w/2;
    ball.y = 480/2 - ball.h/2;

    vx = 3;
    vy = 4;

    started = false;

    keys[0] = SDL_SCANCODE_SPACE;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    bounce = Mix_LoadWAV("bounce.wav");
    bell = Mix_LoadWAV("bell.wav");
}

Ball::~Ball()
{
    Mix_FreeChunk(bounce);
    Mix_FreeChunk(bell);
    Mix_Quit();
}

void Ball::updateBall(const Uint8* keyState) {
    if (keyState[keys[0]] && started == false) {
        started = true;
    }

    if (started) {
        ball.x += vx;
        ball.y += vy;
    }

    if (ball.x + ball.w >= 640 || ball.x <= 0) {
        ball.x = 640/2 - ball.w/2;
        ball.y = 480/2 - ball.h/2;
        Mix_PlayChannel(-1, bell, 0);
    } else if (ball.y + ball.h >= 480 || ball.y <= 0) {
        vy = -vy;
        Mix_PlayChannel(-1, bounce, 0);
    }
}

void Ball::drawBall(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball);
}

void Ball::intersects(Player p) {
    if (ball.x + ball.w >= p.playerRect.x && ball.y + ball.h >= p.playerRect.y && ball.y <= p.playerRect.y + p.playerRect.h && p.getPlayerNumber() == 2) {
        vx = -vx;
        Mix_PlayChannel(-1, bounce, 0);
    } else if (ball.x <= p.playerRect.x + p.playerRect.w && ball.y + ball.h >= p.playerRect.y && ball.y <= p.playerRect.y + p.playerRect.h && p.getPlayerNumber() == 1) {
        vx = -vx;
        Mix_PlayChannel(-1, bounce, 0);
    }
}

void Ball::reset() {
    started = false;
    ball.x = 640/2 - ball.w /2;
    ball.y = 480/2 - ball.h /2;
}
