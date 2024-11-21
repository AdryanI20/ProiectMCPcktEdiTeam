#pragma once

#include "GameState.h"
#include "GameStateMachine.h"
#include <string>

class MainMenuState : public GameState {
public:
    MainMenuState(Game* game) : m_game(game) {};
    void Update() override;
    void Render() override;

    bool onEnter() override;
    bool onExit() override;

    void onKeyDown(SDL_Event* e) override;
    void onKeyUp(SDL_Event* e) override;

    std::string getStateID() const override;
private:
    static const std::string menuID;
    Game* m_game;
};