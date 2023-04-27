#include "Credits.h"

Credits::Credits()
{
    this->currentScene = 4;
}

Credits::~Credits()
{
    this->currentScene = 0;
}

void Credits::drawCredits(SDL_Renderer *renderer, SDL_Event e) {
    char buffer[50];
    time_t t = time(NULL);
    tm* timePointer = localtime(&t);

    sprintf(buffer, "%d", timePointer->tm_year + 1900);

    SDL_Rect rect;

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    TTF_Font *font = nullptr;

    font = TTF_OpenFont("arial.ttf", 30);
    surface = TTF_RenderText_Solid(font, "Made By Azizur Rahaman", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    rect.x = 640/2 - rect.w/2;
    rect.y = 480/2 - rect.h/2;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);

    font = TTF_OpenFont("arial.ttf", 20);
    surface = TTF_RenderText_Solid(font, "Copyright (C) Azizur Rahaman 2017 - ", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    rect.x = 640 - rect.w - 50;
    rect.y = 480 - rect.h - 10;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, buffer, {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    rect.x += rect.w;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, " <-- Go Back ", {0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    rect.x = 15;
    rect.y = 480 - rect.h - 10;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

    if(e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.x >= rect.x && e.button.x <= rect.x + rect.w && e.button.y >= rect.y && e.button.y <= rect.y + rect.h) {
            this->setScene(0);
        }
    }
}

int Credits::getScene() {
    return this->currentScene;
}

void Credits::setScene(int scene) {
    this->currentScene = scene;
}
