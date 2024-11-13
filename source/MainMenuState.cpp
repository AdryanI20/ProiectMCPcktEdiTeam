#include "MainMenuState.h"
#include <iostream>
#include "Game.h"
#include "GameStateMachine.h"

const std::string MainMenuState::menuID = "MENU";

std::string MainMenuState::getStateID() const {
    return menuID;
}

void MenuState::Update() {

}

void MenuState::Render() {

}

bool MenuState::onEnter() {
    return true; //success
}

bool MenuState::onExit() {
    return true;
}

void MenuState::onKeyDown(SDL_Event* e) {

}

void MenuState::onKeyUp(SDL_Event* e) {

}

void MenuState::onMouseButtonDown(SDL_Event& e) {

}

void MenuState::onMouseButtonUp(SDL_Event& e) {

}

void MenuState::onMouseMove(SDL_Event& e) {

}