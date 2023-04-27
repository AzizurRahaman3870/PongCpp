#ifndef MENU_H
#define MENU_H

#include <iostream>

#ifndef SDL_H
    #include <SDL.h>
#endif // SDL_H

#ifndef SDL_TTF_H
    #include <SDL_ttf.h>
#endif // SDL_TTF_H

class Menu
{
    public:
        Menu(SDL_Renderer *renderer);
        virtual ~Menu();

        int getScene();
        void setScene(int scene);
        void drawTitle(SDL_Renderer *renderer);
        void drawOption(SDL_Renderer *renderer, std::string someText, SDL_Color fg, int x, int y);
        void drawMenu(SDL_Renderer *renderer);
        void updateScene(SDL_Event e);

        SDL_Rect menuRect;

    protected:

    private:
        int currentScene;
};

#endif // MENU_H
