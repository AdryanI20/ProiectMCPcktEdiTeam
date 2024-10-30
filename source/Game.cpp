#include "Game.h"
#include "InputHandle.h"

Game::Game() {

}

Game::~Game() {

}

bool Game::Init(const std::string& title, int x, int y, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout << "SDL initialising successful" << std::endl;

        m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);

        if (m_window != nullptr) {
            std::cout << "Window creation succeeded" << std::endl;

            m_renderer = SDL_CreateRenderer(m_window, -1, 0);

            if (m_renderer != nullptr) {
                std::cout << "Renderer creation succeeded" << std::endl;

                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            }
            else {
                std::cout << "Renderer creation failed" << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Window creation failed" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "SDL initalisation failed" << std::endl;
        return false;
    }

    m_inputhandler = new InputHandle();
    m_running = true;
    return true;
}

void Game::Render() {
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Game::HandleEvents() {
    m_inputhandler->Update(this);
}

void Game::Clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::Quit() {
    m_running = false;
}

bool Game::isRunning() {
    return m_running;
}

void Game::Update() {

}
