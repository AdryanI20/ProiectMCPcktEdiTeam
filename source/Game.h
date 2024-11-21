#pragma once
#include "SDL.h"
#include <iostream>
#include <string>
#include "Map.h"
#include "InputHandle.h"
#include "TextureManager.h"
#include "GameStateMachine.h"

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
    //void checkCollisions();
    //void updateBullets();
    //void checkPlayerState();
    //void showText(const std::string& content);
    GameStateMachine* getStateMachine();
    InputHandle* getInputHandler();
    TextureManager* getTextureManager();
    SDL_Renderer* getRenderer();
    Map* getMap();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputHandle* m_inputhandler;
    TextureManager* m_texturemanager;
    Map* m_map;
    //std::vector<Character> m_characters;
    GameStateMachine* m_gameStateMachine;

    bool m_running;
};