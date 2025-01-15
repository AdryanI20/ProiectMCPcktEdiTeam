#pragma once
#include "SDL.h"
#include <string>
#include "InputHandle.h"
#include "TextureManager.h"
#include "GameStateMachine.h"
#include <cpr/cpr.h>
#include <crow.h>

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
    GameStateMachine* getStateMachine();
    InputHandle* getInputHandler();
    TextureManager* getTextureManager();
    SDL_Renderer* getRenderer();
    uint16_t getclientID();
    void setclientID(uint16_t newID);

    std::string getServerLocation();
    void setServerLocation(std::string newLocation);
private:
    void leaveGame();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputHandle* m_inputhandler;
    TextureManager* m_texturemanager;
    GameStateMachine* m_gameStateMachine;

    std::string m_serverLocation;
    bool m_running;
    uint16_t m_clientID;
};