#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>

#ifndef _SDL_H
    #include <SDL.h>
#endif // SDL_H

#ifndef _SDL_TTF_H
        #include <SDL_ttf.h>
#endif // TTF_H

#ifndef _SDL_IMAGE_H
    #include <SDL_image.h>
#endif // SDL_IMAGE_H

class Options
{
    public:
        Options();
        virtual ~Options();

        void drawTitle(SDL_Renderer *renderer);
        void drawOptions(SDL_Renderer *renderer, int x, int y, SDL_Event e);
        short getScene();
        void setScene(short scene);

    protected:

    private:
        bool sound;
        bool buttonPressed;
        short currentScene;
};

#endif // OPTIONS_H
