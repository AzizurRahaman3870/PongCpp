#ifndef CONTROLS_H
#define CONTROLS_H

#include <iostream>

#ifndef _SDL_H
    #include <SDL.h>
#endif // _SDL_H

#ifndef _SDL_TTF_H
    #include <SDL_ttf.h>
#endif // _SDL_TTF_H

class Controls
{
    public:
        Controls();
        virtual ~Controls();
        void drawControls(SDL_Renderer *renderer, SDL_Event e);
        int getScene();
        void setScene(int scene);

    protected:

    private:
        int currentScene;
};

#endif // CONTROLS_H
