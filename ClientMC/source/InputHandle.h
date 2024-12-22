#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"

class Game;
class GameStateMachine;

class InputHandle {
public:
    InputHandle();
    ~InputHandle();

    void Init();
    void Update(Game *game);
    void Clean();

    bool isKeyDown(SDL_Scancode key);
    bool isKeyJustPressed(SDL_Scancode key);

    bool getMouseButtonState(int buttonNum);
    Vector2D* getMousePos();
    void resetMouseStates();
private:
    Vector2D* m_mousePos;
    const uint8_t* m_keystates;
    std::vector<uint8_t> m_OLDkeystates;
    std::vector<bool> m_mouseButtonStates;

    void onKeyDown(SDL_Event* event, GameStateMachine* gameStateMachine);
    void onKeyUp(SDL_Event* event, GameStateMachine* gameStateMachine);

    void onMouseMove(SDL_Event* event, GameStateMachine* gameStateMachine);
    void onMouseButtonDown(SDL_Event* event, GameStateMachine* gameStateMachine);
    void onMouseButtonUp(SDL_Event* event, GameStateMachine* gameStateMachine);
};

enum MOUSE_BUTTONS
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};