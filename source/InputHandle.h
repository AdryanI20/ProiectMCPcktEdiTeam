#pragma once
#include "SDL.h"
#include <vector>

class Game;
class GameStateMachine;

class InputHandle {
public:
    InputHandle();
    ~InputHandle();

    void Init();
    void Update(Game *game);
    void Clean();

    bool isKeyDown(SDL_Scancode key);
    bool isKeyJustPressed(SDL_Scancode key);

private:
    const uint8_t* m_keystates;
    std::vector<uint8_t> m_OLDkeystates;

    void onKeyDown(SDL_Event* event, GameStateMachine* gameStateMachine);
    void onKeyUp(SDL_Event* event, GameStateMachine* gameStateMachine);
};