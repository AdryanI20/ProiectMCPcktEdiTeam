#pragma once
#include "DatabaseManager.h"
#include "GameObject.h"
#include "CellType.h"
#include "BulletObject.h"
#include "PowerUpType.h"
#include <map>
#include <memory>
#include <chrono>

class PlayerObject : public GameObject {
public:
    PlayerObject(Vector2D spawnPos, const std::string& TEX_ID, float fireRate);

    void Update(Map& map, bool shot, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects);
    void setPos(int X, int Y);
    void setPos(Vector2D newPos);
    bool getAlive();
    void setAlive(bool newVal);
    void Respawn();

    Vector2D getFacing();

    bool getHasSpecialBullet() const;
    void setHasSpecialBullet(bool val);
    bool canUseSpecialBullet(bool hasSpecial, bool alive);
private:
    Vector2D m_facing;
    std::weak_ptr<Bullet> m_bullet;
    Vector2D m_spawnPoint;
    int m_lives;
    bool m_alive;
    //bool m_hasSpecialBullet = false; // Indică dacă jucătorul are glonțul special
    PowerUpType m_powerUp;
    float m_fireRate;
    std::chrono::time_point<std::chrono::steady_clock> m_powerUpTimerStart;
    bool m_powerUpActive;

    bool m_hasSpecialBullet = false;

    int m_points;
    int m_finalPosition;
    int m_score;
    
};