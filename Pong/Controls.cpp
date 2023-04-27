#include "Controls.h"

Controls::Controls()
{
    this->currentScene = 3;
}

Controls::~Controls()
{
    this->currentScene = 0;
}

void Controls::drawControls(SDL_Renderer *renderer, SDL_Event e) {

    SDL_Rect Rect;

    TTF_Font *font = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    font = TTF_OpenFont("title_font.ttf", 80);
    surface = TTF_RenderText_Solid(font, "Controls.", {212, 175, 55, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    font = nullptr;
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.x = 640/2 - Rect.w/2;
    Rect.y = 15;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    font = TTF_OpenFont("arial.ttf", 30);
    surface = TTF_RenderText_Solid(font, "Player 1: ", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.x = 70;
    Rect.y = 120;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    surface = TTF_RenderText_Solid(font, "Player 2: ", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.x = Rect.w + 300;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);
    SDL_DestroyTexture(texture);
    texture = nullptr;
    TTF_CloseFont(font);
    font = nullptr;

    font = TTF_OpenFont("arial.ttf", 20);
    surface = TTF_RenderText_Solid(font, "Press Up arrow to go up and ", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x -= 70;
    Rect.y += Rect.h + 20;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    surface = TTF_RenderText_Solid(font, "press down arrow to go down", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.y += 50;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    surface = TTF_RenderText_Solid(font, "Press W key to go up and ", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.x = 15;
    Rect.y -= 50;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    surface = TTF_RenderText_Solid(font, "press S key to go down", {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.y += 50;

    SDL_RenderCopy(renderer, texture, NULL, &Rect);
    SDL_DestroyTexture(texture);

    Rect = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, " <-- Go back ", {0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    surface = nullptr;

    SDL_QueryTexture(texture, NULL, NULL, &Rect.w, &Rect.h);

    Rect.x = 15;
    Rect.y = 480 -Rect.h - 15;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &Rect);
    SDL_RenderCopy(renderer, texture, NULL, &Rect);

    SDL_DestroyTexture(texture);
    texture = nullptr;

    TTF_CloseFont(font);
    font = nullptr;

    if(e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.x >= Rect.x && e.button.x <= Rect.x + Rect.w && e.button.y >= Rect.y && e.button.y <=Rect.y + Rect.h) {
            this->currentScene = 0;
        }
    }
}

int Controls::getScene() {
    return this->currentScene;
}

void Controls::setScene(int scene) {
    this->currentScene = scene;
}
