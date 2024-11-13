#pragma once

#include <string>
#include "SDL.h"

class GameState {
public:
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    virtual void onKeyDown(SDL_Event* e) = 0;
    virtual void onKeyUp(SDL_Event* e) = 0;
    virtual std::string getStateID() const = 0;
protected:

};