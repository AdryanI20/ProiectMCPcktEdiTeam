#include "PlayerObject.h"
#include "Map.h"
#include "CellType.h"
#include <iostream>

PlayerObject::PlayerObject(Vector2D spawnPos, const std::string& TEX_ID)
    : GameObject(spawnPos.getX(), spawnPos.getY(), TEX_ID), m_facing(-1, 0), m_shot(nullptr), m_lives(3), m_alive(true), m_spawnPoint(spawnPos) 
{}

void PlayerObject::Update(Map* map, bool shot, std::map<std::string, GameObject*> gameObjects) {
    bool canMove = true;
    Vector2D newPos = m_pos + m_vel;
    for (const auto& [_, object] : gameObjects) {
        //first check if the object is a powerup, if not continue down here V
        if (object->getPos() == newPos) {
            canMove = false;
            break;
        }
    }
    if (map->getPositionValue(newPos.getX(), newPos.getY()) == CellType::FREE_SPACE && canMove)
        m_pos = newPos;

    //if (map->getPositionValue(m_pos.getX(), m_pos.getY()) == CellType::SPECIAL_ITEM) {
    //    map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
    //    m_hasSpecialBullet = true; // Jucătorul primește glonțul special
    //}

    if (m_vel.getX() != 0 || m_vel.getY() != 0)
        m_facing = m_vel;

    //if (m_pos != oldPos) {
        //map->setPositionValue(oldPos.getX(), oldPos.getY(), m_valBelow);
        //m_valBelow = map->getPositionValue(m_pos.getX(), m_pos.getY());
        //map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::PLAYER);
    //}

    //TODO: id-urile care incerc sa le dau la gloante cateodata se intalnesc si atunci un glont care tocmai ce a fost distrus primeste o functie de rulat din cauza conflictului de ID si el este nullptr
    /*if (shot && m_shot == nullptr) {
        gameObjects.emplace("Bullet" + std::to_string(gameObjects.size()), new Bullet(
            m_pos + m_facing,
            0.11,
            m_facing,
            "Bullet"
        ));
        m_shot = dynamic_cast<Bullet*>(
            STATE->getObjectByID( "Bullet" + std::to_string(STATE->getGameObjects().size() - 1) )
            );
        m_shot->CollideLogic(map, Vector2D(-1, -1), m_pos + m_facing, game);
    }

    if (m_shot) {
        for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
            if (iterator->second == m_shot && m_shot->shouldDestroy()) {
                m_shot = nullptr;
                delete iterator->second;
                gameObjects.erase(iterator);
                break;
            }
        }
    }*/
}

void PlayerObject::Clean() {

}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}

int PlayerObject::getLives()
{
    return m_lives;
}

bool PlayerObject::isAlive()
{
    return m_alive;
}

void PlayerObject::setLivingState(bool state)
{
    m_alive = state;
}

std::string PlayerObject::getID()
{
    return m_textureID;
}

void PlayerObject::givePowerUp(int powerUp)
{
    m_powerUp = static_cast<PowerUpType>(powerUp);
}

void PlayerObject::activatePowerUp(PowerUpType powerUp)
{
    m_powerUpTimer = 3;

    switch (powerUp)
    {
    case NO_POWERUP:
        break;
    case FIRE_RATE:
        m_fireRate /= 2;
        break;
    case BULLET_SPEED:
        break;
    case EXTRA_LIFE:
        m_lives++;
        break;
    case INVINCIBLE:
        break;
    case INVISIBLE:
        break;
    default:
        break;
    }
}

//void PlayerObject::respawn(Map* map)
//{
//    map->setPositionValue(m_pos.getX(), m_pos.getY(), FREE_SPACE);
//    _sleep(500);
//    this->setPos(m_spawnPoint.first, m_spawnPoint.second);
//    map->setPositionValue(m_pos.getX(), m_pos.getY(), PLAYER);
//}

//void PlayerObject::killed(Map* map)
//{
//    m_lives--;
//
//    if (m_lives > 0)
//    {
//        respawn(map);
//    }
//    else
//    {
//        setLivingState(false);
//        map->setPositionValue(m_pos.getX(), m_pos.getY(), FREE_SPACE);
//        Clean();
//    }
//}

Vector2D PlayerObject::getFacing()
{
    return m_facing;
}

//void PlayerObject::Respawn(Game* game)
//{
//    if (m_lives > 0) 
//    {
//        m_lives--;
//        this->setPos(m_spawnPoint.first, m_spawnPoint.second);
//    }
//    else
//    {
//        this->setLivingState(false);
//        std::map<std::string, GameObject*>& gameObjects = game->getStateMachine()->getCurrentState()->getGameObjects();
//        for (auto& obj : gameObjects)
//        {
//            std::string ID = obj.first;
//            if (auto* player = dynamic_cast<PlayerObject*>(obj.second))
//            {
//                if (player->getID() == this->getID())
//                    gameObjects.erase(ID); return;
//            }
//        }
//    }
//}

