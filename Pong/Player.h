#ifndef PLAYER_H
#define PLAYER_H

#ifndef SDL_H
    #include <SDL.h>
#endif // SDL_H

class Player
{
    public:
        Player(int x, int y, int w, int h);
        virtual ~Player();

        void updatePlayer(const Uint8* keyState);
        void drawPlayer(SDL_Renderer *renderer);
        int getPlayerNumber();
        int getScore();
        void addScore();
        void reset();

        SDL_Rect playerRect;

    protected:

    private:
        int score;
        int moveSpeed;
        SDL_Scancode keys[2];
        int playerNum;
};

#endif // PLAYER_H
