#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>

class InputHandle;

class Game {
public:

    Game();
    ~Game();

    bool Init(const std::string& title, int x, int y, int width, int height, int flags);
    void Render();

    void Update();
    void HandleEvents();
    void Clean();
    void Quit();
    bool isRunning();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputHandle* m_inputhandler;

    bool m_running;
};