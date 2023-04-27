#include "Options.h"

Options::Options()
{
    this->sound = true;
    this->buttonPressed = false;
    this->currentScene = 2;
}

Options::~Options()
{
    //dtor
}

void Options::drawTitle(SDL_Renderer *renderer) {
    SDL_Rect optionRect;

    SDL_Surface *textSurface = nullptr;
    SDL_Texture *text = nullptr;
    TTF_Font *font = nullptr;

    font = TTF_OpenFont("title_font.ttf", 80);
    textSurface = TTF_RenderText_Solid(font, "Options", {212, 175, 55, 255});
    text = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_QueryTexture(text, NULL, NULL, &optionRect.w, &optionRect.h);

    optionRect.x = (640/2) - (optionRect.w/2);
    optionRect.y = 50;

    SDL_RenderCopy(renderer, text, NULL, &optionRect);

    SDL_DestroyTexture(text);
}

void Options::drawOptions(SDL_Renderer *renderer, int x, int y, SDL_Event e) {
    SDL_Rect optionRect;

    SDL_Surface *oldImage = nullptr;
    SDL_Texture *newImage = nullptr;

    if(this->sound) {
        oldImage = IMG_Load("sound-on.png");
    } else {
        oldImage = IMG_Load("sound-off.png");
    }

    if (oldImage == NULL || oldImage == nullptr) {
        std::cout<<"Error: "<<IMG_GetError();
    }

    newImage = SDL_CreateTextureFromSurface(renderer, oldImage);

    SDL_FreeSurface(oldImage);

    SDL_QueryTexture(newImage, NULL, NULL, &optionRect.w, &optionRect.h);
    optionRect.w /= 2;
    optionRect.h /= 2;
    optionRect.x = x/2 + optionRect.w/2;
    optionRect.y = y - 50;


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &optionRect);
    SDL_RenderCopy(renderer, newImage, NULL, &optionRect);

    SDL_DestroyTexture(newImage);

    if(e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.x >= optionRect.x && e.button.x <= optionRect.x + optionRect.w && e.button.y >= optionRect.y &&  e.button.y <= optionRect.y + optionRect.h && this->sound) {
            this->buttonPressed = true;
        } else if(e.button.x >= optionRect.x && e.button.x <= optionRect.x + optionRect.w && e.button.y >= optionRect.y &&  e.button.y <= optionRect.y + optionRect.h && !this->sound) {
            this->buttonPressed = true;
        }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        if(e.button.x >= optionRect.x && e.button.x <= optionRect.x + optionRect.w && e.button.y >= optionRect.y &&  e.button.y <= optionRect.y + optionRect.h && this->sound && this->buttonPressed) {
            this->sound = false;
            this->buttonPressed = false;
        } else if(e.button.x >= optionRect.x && e.button.x <= optionRect.x + optionRect.w && e.button.y >= optionRect.y &&  e.button.y <= optionRect.y + optionRect.h && !this->sound && this->buttonPressed) {
            this->sound = true;
            this->buttonPressed = false;
        }
    }

    SDL_Surface *textSurface = nullptr;
    SDL_Texture *text = nullptr;
    TTF_Font *font = nullptr;

    font = TTF_OpenFont("arial.ttf", 24);
    textSurface = TTF_RenderText_Solid(font, " <-- Go back ", {0,0,0,255});

    text = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_QueryTexture(text, NULL, NULL, &optionRect.w, &optionRect.h);

    optionRect.x = 15;
    optionRect.y =  480 - optionRect.h*2;
    optionRect.w += 20;

    SDL_RenderFillRect(renderer, &optionRect);
    SDL_RenderCopy(renderer, text, NULL, &optionRect);

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.x >= optionRect.x && e.button.x <= optionRect.x + optionRect.w && e.button.y >= optionRect.y && e.button.y <= optionRect.y + optionRect.h) {
            this->currentScene = 0;
        }
    }

    SDL_DestroyTexture(text);
}

short Options::getScene() {
    return this->currentScene;
}

void Options::setScene(short scene) {
    if (this->currentScene != scene) {
        this->currentScene = scene;
    }
}
