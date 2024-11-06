#pragma once
#include "SDL.h"
#include <iostream>
#include <string>
#include "Character.h"

class Map;
class InputHandle;
class TextureManager;

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
    void showText(const std::string& content);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputHandle* m_inputhandler;
    TextureManager* m_texturemanager;
    Map* m_map;
    std::vector<Character*> m_gameObjects;

    bool m_running;
};