#include "PlayState.h"
//#include <iostream>
#include "Game.h"
#include "PlayerObject.h"

const std::string PlayState::playID = "PLAY";

std::string PlayState::getStateID() const {
    return playID;
}

void PlayState::Update() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update(m_game->getInputHandler());
    }
}

void PlayState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 33, 149, 199, 255);

    m_game->getTextureManager()->Load(m_game->getMap()->getMapString(), "Map", m_game->getRenderer());

    if (m_game->getTextureManager()->TextureExists("Map"))
        m_game->getTextureManager()->Draw("Map", 0, 0, 2, m_game->getRenderer());
}

bool PlayState::onEnter() {
    std::cout << "entering Play" << std::endl;

    gameObjects.emplace("Player", new PlayerObject(0, 0));
    m_plr = getObjectByID("Player");
    m_valBelowPlr = m_game->getMap()->getPositionValue(m_plr->getPos().getX(), m_plr->getPos().getY());
    m_game->getMap()->setPositionValue(m_plr->getPos().getX(), m_plr->getPos().getY(), CellType::PLAYER);

    return true; //success
}

bool PlayState::onExit() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Clean();
    }
    gameObjects.clear();
    m_game->getTextureManager()->clearFromTextureMap("Map");
    std::cout << "exiting Play" << std::endl;
    return true;
}

void PlayState::onKeyDown(SDL_Event* e) {
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}

void PlayState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}