#ifndef CREDITS_H
#define CREDITS_H

#include <ctime>
#include <iostream>

#ifndef _SDL_H
    #include <SDL.h>
#endif // _SDL_H

#ifndef _SDL_TTF_H
    #include <SDL_ttf.h>
#endif // _SDL_TTF_H

class Credits
{
    public:
        Credits();
        virtual ~Credits();
        void setScene(int scene);
        int getScene();
        void drawCredits(SDL_Renderer *renderer, SDL_Event e);
    protected:

    private:
        int currentScene;
};

#endif // CREDITS_H
