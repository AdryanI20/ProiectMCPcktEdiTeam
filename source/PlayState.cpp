#include "PlayState.h"
//#include <iostream>
#include "Game.h"

const std::string PlayState::playID = "PLAY";

std::string PlayState::getStateID() const {
    return playID;
}

void PlayState::Update() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update(m_game);
    }
}

void PlayState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 33, 149, 199, 255);

    if (m_game->getTextureManager()->TextureExists("Map"))
        m_game->getTextureManager()->clearFromTextureMap("Map");

    m_game->getTextureManager()->LoadText(m_game->getMap()->getMapString(), "Map", m_game->getRenderer());
    
    //m_game->getTextureManager()->Draw("test", 50, 50, 1, m_game->getRenderer(), );
    m_game->getTextureManager()->Draw("Map", 0, 0, 1, m_game->getRenderer());

    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++)
    {
        iterator->second->Draw(m_game->getTextureManager(), m_game->getRenderer());
    }
}

bool PlayState::onEnter() {
    std::cout << "entering Play" << std::endl;

    m_game->getTextureManager()->LoadImage("resources/ship1.png", "Player1", m_game->getRenderer());
    m_game->getTextureManager()->LoadImage("resources/ship2.png", "Player2", m_game->getRenderer());
    m_game->getTextureManager()->LoadImage("resources/ship3.png", "Player3", m_game->getRenderer());
    m_game->getTextureManager()->LoadImage("resources/ship4.png", "Player4", m_game->getRenderer());

    gameObjects.emplace("Player1", 
        new PlayerObject(
            0, 
            0, 
            m_game->getMap()->getPositionValue(0, 0),
            0,
            "Player1"
        ));
    gameObjects.emplace("Player2", 
        new PlayerObject(
            m_game->getMap()->getSize().first-1, 
            0, 
            m_game->getMap()->getPositionValue(m_game->getMap()->getSize().first-1, 0),
            1,
            "Player2"
        ));
    gameObjects.emplace("Player3", 
        new PlayerObject(
            0,
            m_game->getMap()->getSize().second-1,
            m_game->getMap()->getPositionValue(0, m_game->getMap()->getSize().second-1),
            2,
            "Player3"
        ));
    gameObjects.emplace("Player4", 
        new PlayerObject(
            m_game->getMap()->getSize().first-1, 
            m_game->getMap()->getSize().second-1,
            m_game->getMap()->getPositionValue(m_game->getMap()->getSize().first-1, m_game->getMap()->getSize().second-1),
            3,
            "Player4"
        ));
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        m_game->getMap()->setPositionValue(iterator->second->getPos().getX(), iterator->second->getPos().getY(), CellType::PLAYER);
    }

    return true; //success
}

bool PlayState::onExit() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Clean();
    }
    gameObjects.clear();

    if (m_game->getTextureManager()->TextureExists("Map"))
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
