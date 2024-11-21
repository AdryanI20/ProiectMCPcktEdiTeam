#include "MainMenuState.h"
#include <iostream>
#include "TextureManager.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

void MainMenuState::Update() {
    for (it_type iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Update();
    }
}

void MainMenuState::Render(TextureManager* textureManager, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    if (textureManager->TextureExists("MainMenu"))
        textureManager->Draw("MainMenu", 960/4, 100, 2, renderer);
}

bool MainMenuState::onEnter(TextureManager* textureManager, SDL_Renderer* renderer) {
    std::cout << "entering MainMenu" << std::endl;

    textureManager->Load("Game Title", "MainMenu", renderer);

    return true; //success
}

bool MainMenuState::onExit() {
    for (it_type iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->Clean();
    }
    gameObjects.clear();

    std::cout << "exiting MainMenu" << std::endl;
    return true;
}

void MainMenuState::onKeyDown(SDL_Event* e) {
}

void MainMenuState::onKeyUp(SDL_Event* e) {

}