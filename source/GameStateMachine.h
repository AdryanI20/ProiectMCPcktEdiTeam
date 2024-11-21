#pragma once

#include "GameState.h"
#include <vector>
#include "SDL.h"

class GameStateMachine {
public:
    GameStateMachine() = default;
    ~GameStateMachine() = default;

    void pushState(GameState* state, TextureManager* textureManager, SDL_Renderer* renderer);
    void changeState(GameState* state, TextureManager* textureManager, SDL_Renderer* renderer);
    void popState();

    void Update();
    void Render(TextureManager* textureManager, SDL_Renderer* renderer);

    void onKeyDown(SDL_Event* e);
    void onKeyUp(SDL_Event* e);
private:
    std::vector<GameState*> gameStates;
};