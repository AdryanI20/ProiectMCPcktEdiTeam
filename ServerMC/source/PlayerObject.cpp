#include "PlayerObject.h"
#include "Map.h"
#include "CellType.h"
#include <iostream>
#include <format>
#include <string_view>

PlayerObject::PlayerObject(Vector2D spawnPos, const std::string& TEX_ID, float fireRate)
        : GameObject(spawnPos.getX(), spawnPos.getY(), TEX_ID),
          m_facing(-1, 0),
          m_alive(true),
          m_lives(3),
          m_spawnPoint(spawnPos),
          m_hasSpecialBullet(false),  
          m_powerUpActive(false),     
          m_fireRate(fireRate)
{}

uint32_t SDBM_hash(const uint8_t* buf, size_t size) {
    uint32_t hash = 0;
    for (size_t i = 0; i < size; i++)
        hash = (hash << 6) + (hash << 16) - hash + buf[i]; //hash * 65599 + byte
    return hash;
}

void PlayerObject::Update(Map& map, bool shot, std::map<std::string, std::shared_ptr<GameObject> >& gameObjects) {
    if (!m_alive) return;

    bool canMove = true;
    Vector2D newPos = m_pos + m_vel;
    for (const auto& [_, object] : gameObjects) {
        if (object->getPos() == newPos) {
            canMove = false;
            break;
        }
    }
    if (map.getPositionValue(newPos.getX(), newPos.getY()) == CellType::FREE_SPACE && canMove)
        m_pos = newPos;

    
    
    
    

    if (m_powerUpActive) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - m_powerUpTimerStart;
        if (elapsed.count() >= 5.0) {
            
            m_powerUpActive = false;
            switch (m_powerUp) {
                case FIRE_RATE:
                    m_fireRate /= 1.5;
                    break;
                case EXTRA_LIFE:
                    break;
            }
            std::cout << "Power-up a expirat!\n";
        }
    }

    if (m_vel.getX() != 0 || m_vel.getY() != 0)
        m_facing = m_vel;

    if (shot && !m_bullet.lock()) {
        std::string hashKey = std::format("{}{}{}{}{}{}", m_spawnPoint.getX(), m_spawnPoint.getY(), m_vel.getX(), m_vel.getY(), m_pos.getX(), m_pos.getY());
        uint32_t hash = SDBM_hash(reinterpret_cast<const uint8_t*>(hashKey.c_str()), hashKey.size());
        std::shared_ptr<Bullet> newBlt = std::make_shared<Bullet>(
            m_pos + m_facing,
            m_fireRate,
            m_facing,
            ""
        );
        gameObjects.emplace("Bullet" + std::to_string(hash), newBlt);
        m_bullet = newBlt;
        newBlt->CollideLogic(map, gameObjects, Vector2D(-1, -1), m_pos + m_facing);
    }
}

void PlayerObject::setPos(int X, int Y) {
    m_pos = Vector2D(X, Y);
}

void PlayerObject::setPos(Vector2D newPos) {
    m_pos = newPos;
}

bool PlayerObject::getAlive() {
    return m_alive;
}

void PlayerObject::setAlive(bool newVal) {
    m_alive = newVal;
}

void PlayerObject::Respawn() {
    if (m_lives > 0) {
        setPos(m_spawnPoint);
        m_lives--;
    }
    else {
        m_alive = false;
        setPos(-1, -1);
    }
}

Vector2D PlayerObject::getFacing() {
    return m_facing;
}

bool PlayerObject::getHasSpecialBullet() const {
    return m_hasSpecialBullet;
}

void PlayerObject::setHasSpecialBullet(bool val) {
    m_hasSpecialBullet = val;
}
