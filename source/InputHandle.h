#pragma once
#include "SDL.h"

class Game;
class GameStateMachine;

class InputHandle {
public:
    InputHandle();
    ~InputHandle();

    void Init();
    void Update(Game *CurGame);
    void Clean();

    bool isKeyDown(SDL_Scancode key);

private:
    const uint8_t* m_keystates;

    void onKeyDown(SDL_Event* event, GameStateMachine* gameStateMachine);
    void onKeyUp(SDL_Event* event, GameStateMachine* gameStateMachine);
};