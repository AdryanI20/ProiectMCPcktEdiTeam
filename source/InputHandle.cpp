#include "InputHandle.h"
#include "Game.h"
#include <iostream>
#include "GameStateMachine.h"

InputHandle::InputHandle() {

}

InputHandle::~InputHandle() {

}

void InputHandle::Init() {

}

void InputHandle::Update(Game *game) {
    m_keystates = SDL_GetKeyboardState(nullptr);

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->Quit();
                break;

            case SDL_KEYDOWN:
                onKeyDown(&event, game->getStateMachine());
                break;

            case SDL_KEYUP:
                onKeyUp(&event, game->getStateMachine());
                break;

            default:
                break;
        }
    }
}

void InputHandle::Clean() {

}

void InputHandle::onKeyDown(SDL_Event *event, GameStateMachine* gameStateMachine) {
    gameStateMachine->onKeyDown(event);
}

void InputHandle::onKeyUp(SDL_Event *event, GameStateMachine* gameStateMachine) {
    gameStateMachine->onKeyUp(event);
}

bool InputHandle::isKeyDown(SDL_Scancode key) {
    if (m_keystates != nullptr) {
        if (m_keystates[key] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
