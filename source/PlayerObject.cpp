#include "PlayerObject.h"
#include <iostream>
#include "Game.h"

PlayerObject::PlayerObject(int X, int Y, CellType valBelow, int mapping, const std::string& TEX_ID)
    : GameObject(X, Y, TEX_ID), m_facing(-1, 0), m_valBelow(valBelow), inputMap(mapping), m_shot(nullptr) {}

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

    if (m_vel.getX() != 0 || m_vel.getY() != 0)
        m_facing = m_vel;

    if (m_pos != oldPos) {
        map->setPositionValue(oldPos.getX(), oldPos.getY(), m_valBelow);
        m_valBelow = map->getPositionValue(m_pos.getX(), m_pos.getY());
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

    //TODO: id-urile care incerc sa le dau la gloante cateodata se intalnesc si atunci un glont care tocmai ce a fost distrus primeste o functie de rulat din cauza conflictului de ID si el este nullptr
    if (shoot && m_shot == nullptr) {
        GameState* STATE = game->getStateMachine()->getCurrentState();
        STATE->getGameObjects().emplace("Bullet" + std::to_string(STATE->getGameObjects().size()), new Bullet(
            m_pos + m_facing,
            0.11,
            m_facing,
            "Bullet"
        ));
        m_shot = dynamic_cast<Bullet*>(
            STATE->getObjectByID( "Bullet" + std::to_string(STATE->getGameObjects().size() - 1) )
            );
        m_shot->CollideLogic(map, Vector2D(-1, -1), m_pos + m_facing);
    }

    if (m_shot) {
        std::map<std::string, GameObject*>& gameObjects = game->getStateMachine()->getCurrentState()->getGameObjects();
        for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
            if (iterator->second == m_shot && m_shot->shouldDestroy()) {
                m_shot = nullptr;
                delete iterator->second;
                gameObjects.erase(iterator);
                break;
            }
        }
    }
}

void PlayerObject::Clean() {

}

void PlayerObject::Draw(TextureManager* textureManager, SDL_Renderer* renderer) {
    int img_size = 64;
    int angle = 0;
    if (m_facing == Vector2D(-1, 0))
        angle = 180;
    else if (m_facing == Vector2D(1, 0))
        angle = 0;
    else if(m_facing == Vector2D(0, 1))
        angle = 270;
    else if(m_facing == Vector2D(0, -1))
        angle = 90;
    textureManager->Draw(m_textureID, m_pos.getY() * img_size, m_pos.getX() * img_size, 1, renderer, angle);
}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}
