#include "PlayerObject.h"
#include <iostream>
#include "Game.h"

PlayerObject::PlayerObject(int X, int Y, CellType valBelow) : GameObject(X, Y), m_facing(3), m_valBelowPlr(valBelow) {}

void PlayerObject::Update(Game* game) {
    InputHandle* inputHandler = game->getInputHandler();
    Map* map = game->getMap();
    Vector2D oldPos = m_pos;

    m_vel = Vector2D(
        inputHandler->isKeyJustPressed(SDL_SCANCODE_DOWN) - inputHandler->isKeyJustPressed(SDL_SCANCODE_UP),
        inputHandler->isKeyJustPressed(SDL_SCANCODE_RIGHT) - inputHandler->isKeyJustPressed(SDL_SCANCODE_LEFT));

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
        map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::PLAYER);
    }
}

void PlayerObject::Clean() {

}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}
