#include "Game.h"
#include "MainMenuState.h"
#include <iostream>

Game::Game() : m_serverLocation("127.0.0.1") {} //NU FOLOSI LOCALHOST FOLOSESTE 127.0.0.1

Game::~Game() {}

bool Game::Init(const std::string& title, int x, int y, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() < 0) {
        std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << "Error intializing SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (!m_window) {
        std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!m_renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    int img_size = 64;
    SDL_RenderSetLogicalSize(m_renderer, 30*img_size, 30*img_size);
    //shouldnt be hardcoded

    SDL_StartTextInput();

    m_texturemanager = new TextureManager();
    m_inputhandler = new InputHandle();
    m_inputhandler->Init();

    m_running = true;

    m_gameStateMachine = new GameStateMachine();
    m_gameStateMachine->pushState(new MainMenuState(this));
    return true;
}

void Game::Render() {
    SDL_RenderClear(m_renderer);

    m_gameStateMachine->Render();

    SDL_RenderPresent(m_renderer);
}

void Game::HandleEvents() {
    m_inputhandler->Update(this);
}

void Game::Clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    if (SDL_IsTextInputActive() == SDL_TRUE)
        SDL_StopTextInput();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::Quit() {
    leaveGame();
    m_running = false;
}

bool Game::isRunning() {
    return m_running;
}

void Game::Update() {
    m_gameStateMachine->Update();
}

GameStateMachine* Game::getStateMachine() {
    return m_gameStateMachine;
}

InputHandle* Game::getInputHandler()
{
    return m_inputhandler;
}

TextureManager* Game::getTextureManager()
{
    return m_texturemanager;
}

SDL_Renderer* Game::getRenderer()
{
    return m_renderer;
}

int Game::getclientID()
{
    return m_clientID;
}

void Game::setclientID(int newID)
{
    m_clientID = newID;
}

std::string Game::getServerLocation() {
    return m_serverLocation;
}

void Game::setServerLocation(std::string newLocation) {
    m_serverLocation = newLocation;
}

void Game::leaveGame()
{
    cpr::Response r = cpr::Put(cpr::Url{ "http://"+m_serverLocation+":18080/leave_game" },
        cpr::Payload{
            {"clientID", std::to_string(m_clientID)}
        });
}
