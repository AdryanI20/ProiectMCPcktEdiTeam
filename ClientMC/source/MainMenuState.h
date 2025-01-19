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
    void TextShow(const std::string& ID, int posX, int posY, double scale);
    bool JoinGame(std::string username);

    static const std::string menuID;
    Game* m_game;
};