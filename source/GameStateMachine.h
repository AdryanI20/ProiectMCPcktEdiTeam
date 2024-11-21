#pragma once

#include "GameState.h"
#include <vector>
#include "SDL.h"
#include "InputHandle.h"

class GameStateMachine {
public:
    GameStateMachine() = default;
    ~GameStateMachine() = default;

    void pushState(GameState* state);
    void changeState(GameState* state);
    void popState();

    void Update();
    void Render();

    void onKeyDown(SDL_Event* e);
    void onKeyUp(SDL_Event* e);
private:
    std::vector<GameState*> gameStates;
};