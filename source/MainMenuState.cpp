#include "MainMenuState.h"
//#include <iostream>
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

void MainMenuState::Update() {
    for (it_type iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update();
    }
}

void MainMenuState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 30, 30, 30, 255);
    if (m_game->getTextureManager()->TextureExists("MainMenu"))
        m_game->getTextureManager()->Draw("MainMenu", 960/4, 100, 2, m_game->getRenderer());
}

bool MainMenuState::onEnter() {
    std::cout << "entering MainMenu" << std::endl;

    m_game->getTextureManager()->Load("Game Title", "MainMenu", m_game->getRenderer());

    return true; //success
}

bool MainMenuState::onExit() {
    for (it_type iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Clean();
    }
    gameObjects.clear();
    m_game->getTextureManager()->clearFromTextureMap("Game Title");
    std::cout << "exiting MainMenu" << std::endl;
    return true;
}

void MainMenuState::onKeyDown(SDL_Event* e) {
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
    if (m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_RETURN)) { //Enter;
        m_game->getStateMachine()->changeState(new PlayState(m_game));
    }
}

void MainMenuState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}