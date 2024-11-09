#include "Game.h"
#include "InputHandle.h"
#include "TextureManager.h"
#include "Map.h"
#include "Weapon.h"

Game::Game() {

}

Game::~Game() {

}

bool Game::Init(const std::string& title, int x, int y, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() < 0) {
        std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
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

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    m_texturemanager = new TextureManager();
    m_inputhandler = new InputHandle();
    m_map = new Map(30, 30);
    m_map->createRandomMap();

    Character* character = new Character(0, 0, "Nume", std::make_pair<int, int>(0, 0), new Weapon());
    m_characters.push_back(character);

    m_running = true;

    return true;
}

void Game::Render() {
    SDL_RenderClear(m_renderer);
    if (m_texturemanager->TextureExists("text"))
        m_texturemanager->Draw("text", 0, 0, 2, m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Game::HandleEvents() {
    m_inputhandler->Update(this);
}

void Game::Clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    TTF_Quit();
    SDL_Quit();
}

void Game::Quit() {
    m_running = false;
}

bool Game::isRunning() {
    return m_running;
}

void Game::Update() {
    showText(m_map->getMapString());
}

void Game::showText(const std::string &content) {
    if (m_texturemanager->TextureExists("text"))
        m_texturemanager->clearFromTextureMap("text");
    m_texturemanager->Load(content, "text", m_renderer);
}
