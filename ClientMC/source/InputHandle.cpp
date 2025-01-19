#include "InputHandle.h"
#include "Game.h"
#include <iostream>

InputHandle::InputHandle() : m_inputIndex(0) {}

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

            case SDL_TEXTINPUT: {
                if (m_inputIndex < 0 || m_inputIndex >= m_inputs.size()) {
                    if (m_inputIndex >= 0) {
                        m_inputs.resize(m_inputIndex + 1);
                        m_inputs[m_inputIndex] = "";
                    }
                }
                //Not copy or pasting
                if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')))
                {
                    //Append character
                    m_inputs[m_inputIndex] += event.text.text;
                }
            }
                break;

            default:
                break;
        }
    }
}

void InputHandle::Clean() {

}

void InputHandle::onKeyDown(SDL_Event *event, GameStateMachine* gameStateMachine) {
    if (m_inputIndex < 0 || m_inputIndex >= m_inputs.size()) {
        if (m_inputIndex >= 0) {
            m_inputs.resize(m_inputIndex + 1);
            m_inputs[m_inputIndex] = "";
        }
    }
    if (event->key.keysym.sym == SDLK_BACKSPACE && m_inputs[m_inputIndex].length() > 0) {
        m_inputs[m_inputIndex].pop_back();
    }

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

std::string InputHandle::getTextInput(int index) {
    if (index < 0 || index >= m_inputs.size()) {
        if (index >= 0) {
            m_inputs.resize(index + 1);
            m_inputs[index] = "";
        }
    }
    return m_inputs[index];
}

void InputHandle::setInputIndex(int index) {
    m_inputIndex = index;
}
