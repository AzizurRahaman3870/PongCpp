#include "Player.h"

Player::Player(int x, int y, int w, int h)
{
    this->moveSpeed = 5;

    this->playerRect.x = x;
    this->playerRect.y = y;
    this->playerRect.w = w;
    this->playerRect.h = h;

    static int playerNumber = 0;
    playerNumber++;

    if (playerNumber == 1) {
        this->keys[0] = SDL_SCANCODE_W;
        this->keys[1] = SDL_SCANCODE_S;
    } else if (playerNumber == 2) {
        this->keys[0] = SDL_SCANCODE_UP;
        this->keys[1] = SDL_SCANCODE_DOWN;
    }

    this->playerNum = playerNumber;

    this->score = 0;
}

Player::~Player()
{
    this->moveSpeed = 0;
    this->playerRect.x = this->playerRect.y = this->playerRect.w = this->playerRect.h = 0;
    this->score = 0;
    this->playerNum = 0;
}

void Player::updatePlayer(const Uint8* keyState) {
    if (keyState[this->keys[0]] && playerRect.y > 0) {
        this->playerRect.y -= this->moveSpeed;
    } else if (keyState[this->keys[1]] && this->playerRect.y + this->playerRect.h < 480) {
        this->playerRect.y += this->moveSpeed;
    }
}

void Player::drawPlayer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &this->playerRect);
}

int Player::getPlayerNumber() {
    return this->playerNum;
}

int Player::getScore() {
    return this->score;
}

void Player::addScore() {
    this->score++;
}

void Player::reset() {
    this->score = 0;
}
