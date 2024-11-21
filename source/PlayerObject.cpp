#include "PlayerObject.h"
//#include <iostream>

PlayerObject::PlayerObject(int X, int Y) : GameObject(X, Y) {}

void PlayerObject::Update(InputHandle* inputhandler) {
    m_vel = Vector2D(
        inputhandler->isKeyJustPressed(SDL_SCANCODE_DOWN) - inputhandler->isKeyJustPressed(SDL_SCANCODE_UP),
        inputhandler->isKeyJustPressed(SDL_SCANCODE_RIGHT) - inputhandler->isKeyJustPressed(SDL_SCANCODE_LEFT));

    m_pos += m_vel;

    //std::cout << m_pos.getX() << " " << m_pos.getY() << "\n";
}

void PlayerObject::Clean() {

}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}
