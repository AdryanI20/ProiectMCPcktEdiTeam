#pragma once

#include "GameState.h"
#include <string>
#include "CellType.h"

class PlayState : public GameState
{
public:
    PlayState(Game* game) : m_game(game) {};
    void Update() override;
    void Render() override;

    bool onEnter() override;
    bool onExit() override;

    void onKeyDown(SDL_Event* e) override;
    void onKeyUp(SDL_Event* e) override;

    std::string getStateID() const override;// { return playID; }

private:
    static const std::string playID;
    Game* m_game;
    CellType m_valBelowPlr;
    GameObject* m_plr;
};

