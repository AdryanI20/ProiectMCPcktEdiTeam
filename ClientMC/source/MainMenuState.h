#pragma once

//#include "Button.h"
#include "GameState.h"
#include <string>

class MainMenuState : public GameState {
public:
    MainMenuState(Game* game);
    void Update() override;
    void Render() override;

    bool onEnter() override;
    bool onExit() override;

    void onKeyDown(SDL_Event* e) override;
    void onKeyUp(SDL_Event* e) override;
    void onMouseButtonUp(SDL_Event* e) override;
    void onMouseButtonDown(SDL_Event* e) override;
    void onMouseMove(SDL_Event* e) override;

    std::string getStateID() const override;

private:
    bool joinGame();
    //Button m_playButton; // Button for Play
    static const std::string menuID;
    Game* m_game;
};