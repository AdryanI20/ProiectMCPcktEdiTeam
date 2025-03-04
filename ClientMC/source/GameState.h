#pragma once
#include <map>
#include <string>
#include "SDL.h"
#include "GameObject.h"

class GameState {
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    virtual void onKeyDown(SDL_Event* e) = 0;
    virtual void onKeyUp(SDL_Event* e) = 0;
    virtual void onMouseButtonUp(SDL_Event* e) = 0;
    virtual void onMouseButtonDown(SDL_Event* e) = 0;
    virtual void onMouseMove(SDL_Event* e) = 0;
    virtual std::string getStateID() const = 0;

protected:
    std::map<std::string, GameObject*> gameObjects;
    Game* m_game;
};

typedef std::map<std::string, GameObject*>::iterator objs_it;

