#include "PlayerObject.h"
#include <iostream>

PlayerObject::PlayerObject(int X, int Y) : GameObject(X, Y) {}

void PlayerObject::Update(InputHandle* inputhandler) {
    m_vel = Vector2D(
        inputhandler->isKeyJustPressed(SDL_SCANCODE_DOWN) - inputhandler->isKeyJustPressed(SDL_SCANCODE_UP),
        inputhandler->isKeyJustPressed(SDL_SCANCODE_RIGHT) - inputhandler->isKeyJustPressed(SDL_SCANCODE_LEFT));

    m_pos += m_vel;

   // if (keyjuspress(SDL_SCANCODE_SPACE))
     //   gameObjects.emplace("Player", new BulletObjec(0, 0));

    //std::cout << m_vel.getX() << " " << m_vel.getY() << "\n";
}
void PlayerObject::Clean() {

}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}
