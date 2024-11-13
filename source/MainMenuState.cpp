#include "MainMenuState.h"
#include <iostream>

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

void MainMenuState::Update() {

}

void MainMenuState::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
}

bool MainMenuState::onEnter() {
    std::cout << "entering MainMenu" << std::endl;
    return true; //success
}

bool MainMenuState::onExit() {
    std::cout << "exiting MainMenu" << std::endl;
    return true;
}

void MainMenuState::onKeyDown(SDL_Event* e) {
}

void MainMenuState::onKeyUp(SDL_Event* e) {

}