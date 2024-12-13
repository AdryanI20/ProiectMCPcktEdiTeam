#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

bool MainMenuState::joinGame() {
    cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:18080/join_game" });
    if (r.status_code == 200) {
        auto json = crow::json::load(r.text);
        m_game->setclientID(json["clientID"].i());
        return true;
    }
    return false;
}

MainMenuState::MainMenuState(Game* game) : m_game(game) {}

void MainMenuState::Update() {
    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        //iterator->second->Update(m_game->getInputHandler());
    //}
}

void MainMenuState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 30, 30, 30, 255);
    if (m_game->getTextureManager()->TextureExists("MainMenu"))
        m_game->getTextureManager()->Draw("MainMenu", 740/4, 100, 2, m_game->getRenderer());

    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++)
    //{
        //iterator->second->draw();
    //}
}

bool MainMenuState::onEnter() {
    std::cout << "entering MainMenu" << std::endl;

    m_game->getTextureManager()->TextLoad("Game Title", "MainMenu", m_game->getRenderer());

    return true; //success
}

bool MainMenuState::onExit() {
    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        //iterator->second->Clean();
    //}
    //gameObjects.clear();
    m_game->getTextureManager()->clearFromTextureMap("MainMenu");
    std::cout << "exiting MainMenu" << std::endl;
    return true;
}

//TODO: IMPLEMENT MOUSE LOGIC, GUI BUTTONS
void MainMenuState::onKeyDown(SDL_Event* e) {
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
    if (m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_RETURN)) { //Enter;
        if (joinGame()) {
            std::cerr << m_game->getclientID() << std::endl;
            //m_game->getStateMachine()->changeState(new PlayState(m_game));
        }
        else {
            std::cerr << "Couldn't join game" << std::endl;
        }
    }
}

void MainMenuState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}