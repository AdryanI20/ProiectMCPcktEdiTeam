#pragma once
#include <vector>
#include "SDL.h"
#include "InputHandle.h"

class GameState;

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
    void onMouseButtonUp(SDL_Event* e);
    void onMouseButtonDown(SDL_Event* e);
    void onMouseMove(SDL_Event* e);
    GameState* getCurrentState() const;
private:
    std::vector<GameState*> gameStates;
};