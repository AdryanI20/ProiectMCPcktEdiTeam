#pragma once
#include "SDL.h"
#include <iostream>

class Game;

class InputHandle {
public:
    InputHandle();
    ~InputHandle();

    void Init();
    void Update(Game *CurGame);
    void Clean();

    bool isKeyDown(SDL_Scancode key);

private:
    const uint8_t* m_keystates;

    void onKeyDown(SDL_Event* event);
    void onKeyUp(SDL_Event* event);
};