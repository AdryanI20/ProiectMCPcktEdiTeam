#include "InputHandle.h"
#include "Game.h"
//#include <iostream>

InputHandle::InputHandle() {

}

InputHandle::~InputHandle() {

}

void InputHandle::Init() {
    m_keystates = SDL_GetKeyboardState(nullptr);
    m_OLDkeystates.resize(SDL_NUM_SCANCODES, 0);
}

void InputHandle::Update(Game *game) {
    if (m_keystates)
        std::copy(m_keystates, m_keystates + SDL_NUM_SCANCODES, m_OLDkeystates.begin());
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
    return m_keystates != nullptr && m_keystates[key] == 1;
}

bool InputHandle::isKeyJustPressed(SDL_Scancode key) {
    if (m_keystates) {
        // Butonul este apasat acum dar nu a fost apasat ultima data
        return m_keystates[key] == 1 && m_OLDkeystates[key] == 0;
    }
    return false;
}