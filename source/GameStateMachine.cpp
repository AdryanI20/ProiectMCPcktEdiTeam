#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *state) {
    gameStates.push_back(state);
    gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *state) {
    if (!gameStates.empty()) {
        if (gameStates.back()->getStateID() == state->getStateID()) {
            return;
        }
    }

    gameStates.push_back(state);

    if (!gameStates.empty()) {
        if (gameStates.back()->onExit()) {
            gameStates.erase(gameStates.end() - 2);
        }
    }

    gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    if (!gameStates.empty()) {
        if (gameStates.back()->onExit()) {
            gameStates.erase(gameStates.end() - 1);
        }
    }
}

void GameStateMachine::Update() {
    if (!gameStates.empty()) {
        gameStates.back()->Update();
    }
}

void GameStateMachine::Render(SDL_Renderer* renderer) {
    if (!gameStates.empty()) {
        gameStates.back()->Render(renderer);
    }
}

void GameStateMachine::onKeyDown(SDL_Event* e) {
    if (!gameStates.empty()) {
        gameStates.back()->onKeyDown(e);
    }
}

void GameStateMachine::onKeyUp(SDL_Event* e) {
    if (!gameStates.empty()) {
        gameStates.back()->onKeyUp(e);
    }
}