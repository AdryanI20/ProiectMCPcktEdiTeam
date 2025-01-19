#include "Game.h"

int main(int argc, char* args[])
{
    //
    const int FPS = 60;
    const float DELAY_TIME = 1000.0f / FPS;
    uint32_t frameStart, frameTime;
    //

    Game *MainGame = new Game();
    if (!MainGame->Init("Ship Combat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN)) {
        std::cout << "game init failed" << SDL_GetError() << std::endl;
        MainGame->Clean();
        return EXIT_FAILURE;
    }

    while (MainGame->isRunning()) {
        frameStart = SDL_GetTicks();
        MainGame->Update();
        MainGame->HandleEvents();
        MainGame->Render();

        //TODO: Put this piece of code somewhere more relevant, as all it does is cap the game to 60 FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
        else
        {
            SDL_Delay((int)DELAY_TIME);
        }
        //
    }

    MainGame->Clean();

    return 0;
}
