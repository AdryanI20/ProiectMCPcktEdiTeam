#include "Game.h"
//#include "SDL_ttf.h"
//TODO: Move the TTF logic to the texture manager, which will be handled by the Game class.

int main(int argc, char* args[])
{
    /*
    TTF_Font *font = TTF_OpenFont("resources/kongtext.ttf", 64);
    */
    const int FPS = 60;
    const float DELAY_TIME = 1000.0f / FPS;
    uint32_t frameStart, frameTime;

    Game *MainGame = new Game();
    if (MainGame->Init("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, SDL_WINDOW_SHOWN))
    {
        std::cout << "Game Init Succeeded" << std::endl;

        /*
        if (!TTF_Init()) {
            std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
            MainGame->Clean();
            return EXIT_FAILURE;
        }
        if (!font) {
            std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        }
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello World!", textColor);
        if (!textSurface) {
            return EXIT_FAILURE;
        }
        */

        while (MainGame->isRunning())
        {
            frameStart = SDL_GetTicks();
            MainGame->Update();
            MainGame->HandleEvents();
            MainGame->Render();

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
            else
            {
                SDL_Delay((int)DELAY_TIME);
            }
        }
    }
    else
    {
        std::cout << "game init failed" << SDL_GetError() << std::endl;
        return -1;
    }

    /*
    TTF_CloseFont( font );
    TTF_Quit();
    */
    MainGame->Clean();

    return 0;
}
