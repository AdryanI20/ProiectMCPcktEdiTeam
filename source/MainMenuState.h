#pragma once

#include "GameState.h"
#include <string>

class MainMenuState : public GameState {
public:
    virtual void Update();
    virtual void Render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual void onKeyDown(SDL_Event* e);
    virtual void onKeyUp(SDL_Event* e);
    virtual void onMouseButtonUp(SDL_Event& e);
    virtual void onMouseButtonDown(SDL_Event& e);
    virtual void onMouseMove(SDL_Event& e);

    virtual std::string getStateID() const;
private:
    static const std::string menuID;
};