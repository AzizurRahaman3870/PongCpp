#ifndef GLOBALS_H_INCLUDED
    #include "globals.h"
#endif // GLOBALS_H_INCLUDED

void drawText(std::string message, int x, int y, std::string fontName, int fontSize, SDL_Color fg) {
	SDL_Rect textRect;
	SDL_Texture *text = nullptr;

	TTF_Font *font = TTF_OpenFont(fontName.c_str(), fontSize);

	if (font == NULL || font == nullptr) {
		std::cout<<"Cannot Get Font! SDL Error: "<< TTF_GetError();
	}

	SDL_Surface *textMessage = nullptr;
	textMessage = TTF_RenderText_Solid(font, message.c_str(), fg);
	text = SDL_CreateTextureFromSurface(globals::renderer, textMessage);

	if (text == nullptr || text == NULL) {
		std::cout<<"Cannot Get Text! Error: " << TTF_GetError();
	} else if (textMessage == nullptr || textMessage == NULL) {
		std::cout<<"Cannot Get Text! Error: " << SDL_GetError();
	}

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	textRect.x = x;
	textRect.y = y;

	SDL_FreeSurface(textMessage);
	TTF_CloseFont(font);

	if (SDL_RenderCopy(globals::renderer, text, NULL, &textRect)) {
		std::cout<<"Cannot render Text! Error: " << SDL_GetError();
	}

	SDL_DestroyTexture(text);
}

bool init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_FLUIDSYNTH | MIX_INIT_MOD | MIX_INIT_MODPLUG | MIX_INIT_MP3 | MIX_INIT_OGG);
	TTF_Init();

	globals::window = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	globals::renderer = SDL_CreateRenderer(globals::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (globals::window == NULL || globals::window == nullptr || globals::renderer == NULL || globals::renderer == nullptr) {
		std::cout<<"Error: "<<SDL_GetError();
		return false;
	} else {
		return true;
	}
}

void quit() {
	SDL_DestroyRenderer(globals::renderer);
	globals::renderer = nullptr;
	SDL_DestroyWindow(globals::window);
	globals::window = nullptr;
	Mix_CloseAudio();
	globals::keyState = nullptr;

	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}

void capFrameRate (Uint32 starting_tick) {
	if ((1000 / 60) > SDL_GetTicks() - starting_tick) {
		SDL_Delay(1000/60 - (SDL_GetTicks() - starting_tick));
	}
}

void loop() {
	globals::startTime = SDL_GetTicks();
	bool running = true;
	SDL_Event e;

	while (running) {
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			} else if (e.type == SDL_MOUSEBUTTONDOWN && globals::menu.getScene() == 0) {
                globals::menu.updateScene(e);
			}
		}
		globals::keyState = SDL_GetKeyboardState(NULL);

		// Clear
		SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, 255);
		SDL_RenderClear(globals::renderer);

        if (globals::menu.getScene() == 0) {

            globals::menu.drawMenu(globals::renderer);

        } else if (globals::menu.getScene() == 1) {

            if (globals::player1.getScore() >= 10) {
                globals::gameOver = true;
                drawText("Game Over! Player 1 Wins!", globals::SCREEN_WIDTH/2 - 180, globals::SCREEN_HEIGHT/2 - 170, "arial.ttf", 28, {255, 255, 255,255});
            } else if (globals::player2.getScore() >= 10) {
                globals::gameOver = true;
                drawText("Game Over! Player 2 Wins!", globals::SCREEN_WIDTH/2 - 180, globals::SCREEN_HEIGHT/2 - 170, "arial.ttf", 28, {255, 255, 255, 255});
            }

            if (globals::gameOver) {
                SDL_Rect backgroundRect;
                backgroundRect.x = globals::SCREEN_WIDTH/2 - 215;
                backgroundRect.y = globals::SCREEN_HEIGHT/2  + 170;
                backgroundRect.w = 155;
                backgroundRect.h = 35;

                SDL_SetRenderDrawColor(globals::renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(globals::renderer, &backgroundRect);
                drawText("Play Again?", globals::SCREEN_WIDTH/2 - 210, globals::SCREEN_HEIGHT/2 + 170, "arial.ttf", 28, {0, 0, 0, 255});

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if(e.button.x >= backgroundRect.x && e.button.x <= backgroundRect.x + backgroundRect.w && e.button.y >= backgroundRect.y && e.button.y <= backgroundRect.y + backgroundRect.h) {
                        globals::player1.reset();
                        globals::player2.reset();
                        globals::ball.reset();
                        globals::gameOver = false;
                    }
                }

                backgroundRect.x = globals::SCREEN_WIDTH/2 - 10;
                backgroundRect.y = globals::SCREEN_HEIGHT/2 + 170;
                backgroundRect.w = 280;
                SDL_RenderFillRect(globals::renderer, &backgroundRect);
                drawText("<--- Go Back to Menu", globals::SCREEN_WIDTH/2 - 5, globals::SCREEN_HEIGHT/2 + 170, "arial.ttf", 28, {0, 0, 0, 255});

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if(e.button.x >= backgroundRect.x && e.button.x <= backgroundRect.x + backgroundRect.w && e.button.y >= backgroundRect.y && e.button.y <= backgroundRect.y + backgroundRect.h) {
                        globals::menu.setScene(0);
                    }
                }
            }


            if (!globals::gameOver) {
                if (globals::soundPlayed == true) {
                    globals::soundPlayed = false;
                }
                // Update
                globals::player1.updatePlayer(globals::keyState);
                globals::player2.updatePlayer(globals::keyState);
                globals::ball.updateBall(globals::keyState);

                //Check Intersection
                if (globals::ball.ball.x > globals::SCREEN_WIDTH/2) {
                    if (globals::ball.ball.x >= globals::player2.playerRect.x + globals::player2.playerRect.w) {
                        globals::player1.addScore();
                    } else {
                        globals::ball.intersects(globals::player2);
                    }
                } else if (globals::ball.ball.x < globals::SCREEN_WIDTH/2) {
                    if (globals::ball.ball.x + globals::ball.ball.w <= globals::player1.playerRect.x ) {
                        globals::player2.addScore();
                    } else {
                        globals::ball.intersects(globals::player1);
                    }
                }

                //Draw
                globals::player1.drawPlayer(globals::renderer);
                globals::player2.drawPlayer(globals::renderer);
                globals::ball.drawBall(globals::renderer);

                drawText("Score:", globals::SCREEN_WIDTH/2 - 20, globals::SCREEN_HEIGHT/2 - 170, "arial.ttf", 24, {255, 255, 255, 255});
                drawText(std::to_string(globals::player1.getScore()), globals::SCREEN_WIDTH/2 - 130, globals::SCREEN_HEIGHT/2 - 120, "arial.ttf", 30, {255, 255, 255, 255});
                drawText(std::to_string(globals::player2.getScore()), globals::SCREEN_WIDTH/2 + 130, globals::SCREEN_HEIGHT/2 - 120, "arial.ttf", 30, {255, 255, 255, 255});

            }

            if (globals::gameOver == true) {
                if (globals::soundPlayed == false) {
                    Mix_Chunk *winSound = Mix_LoadWAV("win_sound.wav");
                    if (winSound == NULL || winSound == nullptr) {
                        std::cout<<"Cannot Play WinSound! " << Mix_GetError();
                    } else {
                        Mix_PlayChannel(-1, winSound, 0);
                        globals::soundPlayed = true;
                    }
                    Mix_FreeChunk(winSound);
                    winSound = nullptr;
                }
            }

        } else if (globals::menu.getScene() == 2) {

            globals::options.setScene(globals::menu.getScene());
            globals::options.drawTitle(globals::renderer);
            globals::options.drawOptions(globals::renderer, globals::SCREEN_WIDTH/2, globals::SCREEN_HEIGHT/2, e);
            globals::menu.setScene(globals::options.getScene());

        } else if (globals::menu.getScene() == 3) {

            globals::controls.setScene(globals::menu.getScene());
            globals::controls.drawControls(globals::renderer, e);
            globals::menu.setScene(globals::controls.getScene());


        } else if (globals::menu.getScene() == 4) {

            globals::credits.setScene(globals::menu.getScene());
            globals::credits.drawCredits(globals::renderer, e);
            globals::menu.setScene(globals::credits.getScene());

        }

		// Render Current Frame
		SDL_RenderPresent(globals::renderer);

		capFrameRate(globals::startTime);
	}

	quit();
}

int main(int argc, char* argv[])
{
	if (!init()) {
		exit(0);
	}

	loop();
}
