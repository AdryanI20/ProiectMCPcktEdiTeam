#include "PlayerObject.h"
#include <iostream>
#include "Game.h"

PlayerObject::PlayerObject(int X, int Y, CellType valBelow, int mapping) : GameObject(X, Y), m_facing(3), m_valBelowPlr(valBelow), inputMap(mapping) {}

void PlayerObject::Update(Game* game) {
    InputHandle* inputHandler = game->getInputHandler();
    Map* map = game->getMap();
    Vector2D oldPos = m_pos;

    switch (inputMap)
    {
    case 0:
        m_vel = Vector2D(
            inputHandler->isKeyJustPressed(SDL_SCANCODE_DOWN) - inputHandler->isKeyJustPressed(SDL_SCANCODE_UP),
            inputHandler->isKeyJustPressed(SDL_SCANCODE_RIGHT) - inputHandler->isKeyJustPressed(SDL_SCANCODE_LEFT));
        break;
    case 1:
        m_vel = Vector2D(
            inputHandler->isKeyJustPressed(SDL_SCANCODE_S) - inputHandler->isKeyJustPressed(SDL_SCANCODE_W),
            inputHandler->isKeyJustPressed(SDL_SCANCODE_D) - inputHandler->isKeyJustPressed(SDL_SCANCODE_A));
        break;
    case 2:
        m_vel = Vector2D(
            inputHandler->isKeyJustPressed(SDL_SCANCODE_G) - inputHandler->isKeyJustPressed(SDL_SCANCODE_T),
            inputHandler->isKeyJustPressed(SDL_SCANCODE_H) - inputHandler->isKeyJustPressed(SDL_SCANCODE_F));
        break;
    case 3:
        m_vel = Vector2D(
            inputHandler->isKeyJustPressed(SDL_SCANCODE_K) - inputHandler->isKeyJustPressed(SDL_SCANCODE_I),
            inputHandler->isKeyJustPressed(SDL_SCANCODE_L) - inputHandler->isKeyJustPressed(SDL_SCANCODE_J));
        break;
    }
    
    Vector2D newPos = m_pos + m_vel;
    if (map->getPositionValue(newPos.getX(), newPos.getY()) == CellType::FREE_SPACE)
        m_pos = newPos;

    if (m_vel.getX() == -1 && m_vel.getY() == 0)
        m_facing = 0; //UP
    else if (m_vel.getX() == 0 && m_vel.getY() == 1)
        m_facing = 1; //DOWN
    else if (m_vel.getX() == 0 && m_vel.getY() == -1)
        m_facing = 2; //LEFT
    else if (m_vel.getX() == 1 && m_vel.getY() == 0)
        m_facing = 3; //RIGHT

    if (m_pos != oldPos) {
        map->setPositionValue(oldPos.getX(), oldPos.getY(), m_valBelowPlr);
        m_valBelowPlr = map->getPositionValue(m_pos.getX(), m_pos.getY());
        map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::PLAYER);
    }

    bool shoot = false;
    switch (inputMap)
    {
    case 0:
        if (inputHandler->isKeyJustPressed(SDL_SCANCODE_Z))
            shoot = true;
        break;
    case 1:
        if (inputHandler->isKeyJustPressed(SDL_SCANCODE_X))
            shoot = true;
        break;
    case 2:
        if (inputHandler->isKeyJustPressed(SDL_SCANCODE_C))
            shoot = true;
        break;
    case 3:
        if (inputHandler->isKeyJustPressed(SDL_SCANCODE_V))
            shoot = true;
        break;
    }

    if (shoot) {
        std::map<std::string, GameObject*>& objs = game->getStateMachine()->getCurrentState()->getGameObjects();
        objs.emplace("Bullet" + std::to_string(objs.size()), new Bullet(0, 0, 1, m_facing));
    }
}

void PlayerObject::Clean() {

}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}
