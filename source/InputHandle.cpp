#include "InputHandle.h"
#include "Game.h"
#include <iostream>

InputHandle::InputHandle() {

}

InputHandle::~InputHandle() {

}

void InputHandle::Init() {

}

void InputHandle::Update(Game *CurGame) {
    m_keystates = SDL_GetKeyboardState(nullptr);

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                CurGame->Quit();
                break;

            case SDL_KEYDOWN:
                onKeyDown(&event);
                break;

            case SDL_KEYUP:
                onKeyUp(&event);
                break;

            default:
                break;
        }
    }
}

void InputHandle::Clean() {

}

void InputHandle::onKeyDown(SDL_Event *event) {
    std::cout << "Key Pressed: " << SDL_GetKeyName(event->key.keysym.sym) << std::endl;
}

void InputHandle::onKeyUp(SDL_Event *event) {
    std::cout << "Key Released: " << SDL_GetKeyName(event->key.keysym.sym) << std::endl;
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
