#pragma once
#include "GameObject.h"
#include <map>
#include <string>
#include "SDL.h"

class TextureManager;

class GameState {
public:
    virtual void Update() = 0;
    virtual void Render(TextureManager* textureManager, SDL_Renderer* renderer) = 0;
    virtual bool onEnter(TextureManager* textureManager, SDL_Renderer* renderer) = 0;
    virtual bool onExit() = 0;
    virtual void onKeyDown(SDL_Event* e) = 0;
    virtual void onKeyUp(SDL_Event* e) = 0;
    virtual std::string getStateID() const = 0;
    GameObject* getObjectByID(std::string id) { return gameObjects[id]; }
protected:
    std::map<std::string, GameObject*> gameObjects;

};

typedef std::map<std::string, GameObject*>::iterator it_type;