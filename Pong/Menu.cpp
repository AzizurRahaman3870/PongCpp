#include "Menu.h"

Menu::Menu(SDL_Renderer *renderer)
{
    this->currentScene = 0;
}

Menu::~Menu()
{
    this->currentScene = 0;
}

int Menu::getScene() {
    return currentScene;
}

void Menu::setScene(int scene) {
    this->currentScene = scene;
}

void Menu::drawTitle(SDL_Renderer *renderer) {

    SDL_Surface *textSurface = nullptr;
    TTF_Font *font = nullptr;
    SDL_Texture *text = nullptr;

    font = TTF_OpenFont("title_font.ttf", 150);
    textSurface = TTF_RenderText_Solid(font, "Pong!", {0, 0, 0, 255});

    if (font == NULL || font == nullptr || textSurface == NULL || textSurface == nullptr) {
        std::cout<<"Error: " << SDL_GetError() << " TTF_Error: " << TTF_GetError();
    }

    text = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (text == NULL || text == nullptr) {
        std::cout<<"Error: " << SDL_GetError();
    }

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_QueryTexture(text, NULL, NULL, &menuRect.w, &menuRect.h);

    menuRect.x = (640/2) - (menuRect.w/2);
    menuRect.y = 15;

    SDL_RenderCopy(renderer, text, NULL, &menuRect);

    SDL_DestroyTexture(text);
}

void Menu::drawOption(SDL_Renderer *renderer, std::string someText, SDL_Color fg, int x, int y) {
    SDL_Rect optionRect;

    optionRect.x = x;
    optionRect.y = y;

    SDL_Surface *textSurface = nullptr;
    SDL_Texture *text = nullptr;
    TTF_Font *font = nullptr;

    font = TTF_OpenFont("arial.ttf", 24);
    textSurface = TTF_RenderText_Solid(font, someText.c_str(), fg);
    text = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_QueryTexture(text, NULL, NULL, &optionRect.w, &optionRect.h);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &optionRect);
    SDL_RenderCopy(renderer, text, NULL, &optionRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_DestroyTexture(text);
}


void Menu::drawMenu(SDL_Renderer *renderer) {
    menuRect.x = 15;
    menuRect.y = 15;
    menuRect.w = 640-30;
    menuRect.h = 480-30;

    SDL_SetRenderDrawColor(renderer, 120, 120, 255, 255);
    SDL_RenderFillRect(renderer, &menuRect);

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    TTF_Font *font = nullptr;

    font = TTF_OpenFont("arial.ttf", 18);
    surface = TTF_RenderText_Solid(font, "Copyright (C) Azizur Rahaman 2017", {0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, NULL, NULL, &menuRect.w, &menuRect.h);

    menuRect.x = 640 - menuRect.w - 40;
    menuRect.y = 480 -menuRect.h - 20;

    SDL_RenderCopy(renderer, texture, NULL, &menuRect);

    SDL_DestroyTexture(texture);

    this->drawTitle(renderer);

    menuRect.x = menuRect.y = 15;

    menuRect.w = menuRect.h = 0;

    this->drawOption(renderer, "Play!", {0, 0, 0, 255}, menuRect.x + 280, menuRect.y + 170);
    this->drawOption(renderer, "Options", {0, 0, 0, 255}, menuRect.x + 270, menuRect.y + 210);
    this->drawOption(renderer, "Controls", {0, 0, 0, 255}, menuRect.x + 270, menuRect.y + 250);
    this->drawOption(renderer, "Credits", {0, 0, 0, 255}, menuRect.x + 275, menuRect.y + 290);
}

void Menu::updateScene(SDL_Event e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.x >= menuRect.x + 280 && e.button.x <= menuRect.x + 280 + 55 && e.button.y >= menuRect.y + 170 && e.button.y <= menuRect.y + 170 + 28) {
            this->currentScene = 1;
        } else if (e.button.x >= menuRect.x + 270 && e.button.x <= menuRect.x + 270 + 84 && e.button.y >= menuRect.y + 210 && e.button.y <= menuRect.y + 210 + 28) {
            this->currentScene = 2;
        } else if (e.button.x >= menuRect.x + 270 && e.button.x <= menuRect.x + 270 + 90 && e.button.y >= menuRect.y + 250 && e.button.y <= menuRect.y + 250 + 28) {
            this->currentScene = 3;
        } else if (e.button.x >= menuRect.x + 275 && e.button.x <= menuRect.x + 275 + 76 && e.button.y >= menuRect.y + 290 && e.button.y <= menuRect.y + 290 + 28) {
            this->currentScene = 4;
        }
    }
}
