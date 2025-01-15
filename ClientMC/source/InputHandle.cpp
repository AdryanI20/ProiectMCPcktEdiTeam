#include "InputHandle.h"
#include "Game.h"
#include <iostream>

InputHandle::InputHandle() {}

InputHandle::~InputHandle() {}

void InputHandle::Init() {
    for (int i = 0; i < 3; i++)
        m_mouseButtonStates.push_back(false);

    m_keystates = SDL_GetKeyboardState(nullptr);
    m_OLDkeystates.resize(SDL_NUM_SCANCODES, 0);

    m_mousePos = new Vector2D(0, 0);
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

            case SDL_MOUSEMOTION:
                onMouseMove(&event, game->getStateMachine());
                break;

            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(&event, game->getStateMachine());
                break;

            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(&event, game->getStateMachine());
                break;

            case SDL_TEXTEDITING:
                //TODO
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

void InputHandle::onMouseMove(SDL_Event* event, GameStateMachine* gameStateMachine) {
    m_mousePos->setX(event->motion.x);
    m_mousePos->setY(event->motion.y);

    gameStateMachine->onMouseMove(event);
}

void InputHandle::onMouseButtonDown(SDL_Event* event, GameStateMachine* gameStateMachine) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    }
    else if (event->button.button = SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    }
    else if (event->button.button = SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }

    gameStateMachine->onMouseButtonDown(event);
}

void InputHandle::onMouseButtonUp(SDL_Event* event, GameStateMachine* gameStateMachine) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
    }
    else if (event->button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    }
    else if (event->button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }

    gameStateMachine->onMouseButtonUp(event);
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

bool InputHandle::getMouseButtonState(int buttonNum)
{
    return m_mouseButtonStates[buttonNum];
}

Vector2D* InputHandle::getMousePos()
{
    return m_mousePos;
}

void InputHandle::resetMouseStates() {
    for (int i = 0; i < m_mouseButtonStates.size(); i++)
        m_mouseButtonStates[i] = false;
}
