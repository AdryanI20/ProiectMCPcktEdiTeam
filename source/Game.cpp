#include "Game.h"
//#include "Weapon.h"
#include "MainMenuState.h"

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

    //SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    m_texturemanager = new TextureManager();
    m_inputhandler = new InputHandle();
    m_map = new Map(30, 30);
    m_map->createRandomMap();

    //Weapon weapon_test;
    //Character character("Nume", std::make_pair<float, float>(0, 0), weapon_test);
    //m_characters.push_back(character);

    m_running = true;

    m_gameStateMachine = new GameStateMachine();
    m_gameStateMachine->pushState(new MainMenuState(this));
    //TODO: MOVE ALL RELEVANT LOGIC FROM MAIN LOOP OF GAME TO DIFFERENT STATES
    return true;
}

void Game::Render() {
    SDL_RenderClear(m_renderer);

    m_gameStateMachine->Render();
//    if (m_texturemanager->TextureExists("text"))
//        m_texturemanager->Draw("text", 0, 0, 2, m_renderer);
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
    m_gameStateMachine->Update();
//    showText(m_map->getMapString());
}

//void Game::checkCollisions()
//{
//    for (auto& character : m_characters)
//    {
//        auto& bullets = character.getPlayerBullets();
//        for (int i = 0; i < bullets.size(); i++)
//        {
//            if (m_map->getPosition(bullets[i].getPosition().first, bullets[i].getPosition().second) != FREE_SPACE)
//            {
//                m_map->manageCollision(bullets[i].getPosition().first, bullets[i].getPosition().second);
//                character.deleteBullet(i);
//            }
//        }
//    }
//}


//void Game::showText(const std::string &content) {
//    if (m_texturemanager->TextureExists("text"))
//        m_texturemanager->clearFromTextureMap("text");
//    m_texturemanager->Load(content, "text", m_renderer);
//}

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

Map* Game::getMap()
{
    return m_map;
}

