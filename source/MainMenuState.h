#pragma once

#include "GameState.h"
#include "GameStateMachine.h"
#include <string>

class MainMenuState : public GameState {
public:
    void Update() override;
    void Render(TextureManager* textureManager, SDL_Renderer* renderer) override;

    bool onEnter(TextureManager* textureManager, SDL_Renderer* renderer) override;
    bool onExit() override;

    void onKeyDown(SDL_Event* e) override;
    void onKeyUp(SDL_Event* e) override;

    std::string getStateID() const override;
private:
    static const std::string menuID;
};