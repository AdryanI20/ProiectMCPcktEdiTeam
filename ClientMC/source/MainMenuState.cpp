#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "ButtonObject.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

MainMenuState::MainMenuState(Game* game)
    : m_game(game) {//, m_playButton(500, 500, 200, 200, "Play") {  // Define position and size of the button
    // Constructor code
}

void MainMenuState::Update() {
    for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update(m_game);
    }

    if (gameObjects.contains("PlayButton")) {
        auto PlayButton = dynamic_cast<ButtonObject*>(gameObjects["PlayButton"]);
        if (PlayButton->getFlag())
            m_game->getStateMachine()->changeState(new PlayState(m_game));
    }

}

void MainMenuState::Render() {
    SDL_SetRenderDrawColor(m_game->getRenderer(), 30, 30, 30, 255);
    int w, h;
    SDL_GetRendererOutputSize(m_game->getRenderer(), &w, &h);
    if (m_game->getTextureManager()->TextureExists("MainMenu"))
        m_game->getTextureManager()->Draw("MainMenu", 600, 80, 3, m_game->getRenderer());
    
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
    m_game->getTextureManager()->TextLoad("Play", "PlayButton", m_game->getRenderer());
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
            Vector2D(200, 160),
            Vector2D(100, 50),
            img_size,
            1,
            "",
            ""
        ));

    //m_game->getTextureManager()->DrawButton("PlayButton", m_playButton, m_game->getRenderer());

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

//TODO: IMPLEMENT MOUSE LOGIC, GUI BUTTONS
void MainMenuState::onKeyDown(SDL_Event* e) {
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
    
    //if (m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_RETURN)) { //Enter;
        //if (joinGame()) {
            //m_game->getStateMachine()->changeState(new PlayState(m_game));
        //}
        //else {
            //std::cerr << "Couldn't join game" << std::endl;
        //}
    //}
}

void MainMenuState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}

void MainMenuState::onMouseButtonUp(SDL_Event* e) {

}

void MainMenuState::onMouseButtonDown(SDL_Event* e) {
    //int mouseX = e->button.x;
    //int mouseY = e->button.y;

    //if (m_playButton.IsClicked(mouseX, mouseY)) {
        //m_game->getStateMachine()->changeState(new PlayState(m_game));
    //}
}


void MainMenuState::onMouseMove(SDL_Event* e) {

}
