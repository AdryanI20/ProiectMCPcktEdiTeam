#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "ButtonObject.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

MainMenuState::MainMenuState(Game* game)
    : m_game(game) {
}

void MainMenuState::Update() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update(m_game);
    }

    if (gameObjects.contains("PlayButton")) {
        auto PlayButton = dynamic_cast<ButtonObject*>(gameObjects["PlayButton"]);
        if (PlayButton->getFlag()) {
            if (gameObjects.contains("ServerButton")) {
                auto ServerButton = dynamic_cast<ButtonObject*>(gameObjects["ServerButton"]);
                m_game->setServerLocation(ServerButton->getText());
                m_game->getStateMachine()->changeState(new PlayState(m_game));
            }
        }
    }

}

void MainMenuState::TextShow(const std::string& ID, int posX, int posY, double scale) {
    if (m_game->getTextureManager()->TextureExists(ID))
        m_game->getTextureManager()->Draw(ID, posX, posY, scale, m_game->getRenderer());
}

void MainMenuState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 30, 30, 30, 255);
    //int w, h;
    //SDL_GetRendererOutputSize(m_game->getRenderer(), &w, &h);
    //if (m_game->getTextureManager()->TextureExists("MainMenu"))
        //m_game->getTextureManager()->Draw("MainMenu", 600, 80, 3, m_game->getRenderer());
    TextShow("MainMenu", 600, 80, 3);
    TextShow("serverIP", 150, 560, 3);
    TextShow("Username", 5, 1000, 3);
    
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Draw(m_game->getTextureManager(), m_game->getRenderer());
    }
    //if(m_game->getTextureManager()->TextureExists("PlayButton"))
        //m_game->getTextureManager()->DrawButton("PlayButton", m_playButton, m_game->getRenderer());
}

bool MainMenuState::onEnter() {
    std::cout << "entering MainMenu" << std::endl;
    int img_size = 4;

    m_game->getTextureManager()->TextLoad("Ship Combat", "MainMenu", m_game->getRenderer());
    m_game->getTextureManager()->TextLoad("Please input server IP:", "serverIP", m_game->getRenderer());
    m_game->getTextureManager()->TextLoad("Please input your username:", "Username", m_game->getRenderer());
    m_game->getTextureManager()->TextLoad("Play", "PlayButton", m_game->getRenderer());
    m_game->getTextureManager()->TextLoad(" ", "ServerButton", m_game->getRenderer());
    m_game->getTextureManager()->TextLoad(" ", "LoginButton", m_game->getRenderer());
    gameObjects.emplace("PlayButton",
        new ButtonObject(
            Vector2D(200, 80),
            Vector2D(100, 50),
            img_size,
            0,
            "PlayButton",
            ""
        ));
    gameObjects.emplace("ServerButton",
        new ButtonObject(
            Vector2D(150, 170),
            Vector2D(200, 50),
            img_size,
            1,
            "ServerButton",
            "",
            1
        ));
    gameObjects.emplace("LoginButton",
        new ButtonObject(
            Vector2D(150, 280),
            Vector2D(200, 50),
            img_size,
            1,
            "LoginButton",
            "",
            2
        ));

    return true; //success
}

bool MainMenuState::onExit() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Clean();
    }
    gameObjects.clear();
    m_game->getTextureManager()->clearFromTextureMap("MainMenu");
    std::cout << "exiting MainMenu" << std::endl;
    return true;
}

void MainMenuState::onKeyDown(SDL_Event* e) {
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
    
}

void MainMenuState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}

void MainMenuState::onMouseButtonUp(SDL_Event* e) {

}

void MainMenuState::onMouseButtonDown(SDL_Event* e) {

}


void MainMenuState::onMouseMove(SDL_Event* e) {

}
