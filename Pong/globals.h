#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <iostream>
#include <string>

#ifndef MAIN_ICON
    #define MAIN_ICON
#endif // MAIN_ICON

#ifndef SDL_MAIN_HANDLED
    #define SDL_MAIN_HANDLED
#endif // SDL_MAIN_HANDLED

#ifndef SDL_H
    #include <SDL.h>
#endif // SDL_H

#ifndef SDL_MIXER_H
    #include <SDL_mixer.h>
#endif // SDL_MIXER_H

#ifndef SDL_TTF_H
    #include <SDL_ttf.h>
#endif // SDL_TTF_H

#ifndef PLAYER_H
    #include "player.h"
#endif // PLAYER_H

#ifndef BALL_H
    #include "ball.h"
#endif // BALL_H

#ifndef MENU_H
    #include "menu.h"
#endif // MENU_H

#ifndef OPTIONS_H
    #include "Options.h"
#endif // OPTIONS_H

#ifndef CONTROLS_H
    #include "controls.h"
#endif // CONTROLS_H

#ifndef CREDITS_H
    #include "credits.h"
#endif // CREDITS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    bool gameOver = false;

    SDL_Window* window = nullptr;
    SDL_Renderer *renderer = nullptr;
    const Uint8* keyState = nullptr;
    Uint32 startTime = 0;
    bool soundPlayed = false;

    Player player1(15, SCREEN_HEIGHT/2, 10, 60);
    Player player2(SCREEN_WIDTH - 25, SCREEN_HEIGHT/2, 10, 60);
    Ball ball;
    Menu menu(renderer);
    Options options;
    Controls controls;
    Credits credits;

};

#endif // GLOBALS_H_INCLUDED
