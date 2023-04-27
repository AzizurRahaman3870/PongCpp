#ifndef BALL_H
#define BALL_H

#ifndef SDL_MIXER_H
    #include <SDL_mixer.h>
#endif // SDL_MIXER_H

#ifndef PLAYER_H
    #include "player.h"
#endif // PLAYER_H

class Ball
{
    public:
        Ball();
        virtual ~Ball();

        void updateBall(const Uint8* keyState);
        void drawBall(SDL_Renderer *renderer);
        void intersects(Player p);
        void reset();

        SDL_Rect ball;

    protected:

    private:
        bool started;
        int vx, vy;
        Mix_Chunk *bounce;
        Mix_Chunk *bell;
        SDL_Scancode keys[1];
};

#endif // BALL_H
