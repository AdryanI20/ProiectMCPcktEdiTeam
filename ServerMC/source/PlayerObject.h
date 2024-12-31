#pragma once
#include "GameObject.h"
#include "CellType.h"
#include "BulletObject.h"
#include "PowerUpType.h"

class PlayerObject : public GameObject {
public:
    PlayerObject(int X, int Y, CellType valBelow, int mapping, const std::string& TEX_ID);

    void Update() override;
    void Clean() override;
    void setPos(int X, int Y);
    bool hasSpecialBullet() const { return m_hasSpecialBullet; }
    void useSpecialBullet() { m_hasSpecialBullet = false; } // Consumă glonțul special
    void givePowerUp(int powerUp);

    int getLives();
    bool isAlive();
    std::string getID() override;
    void setLivingState(bool state);
    void respawn(Map* map);
    void killed(Map* map);
private:
    Vector2D m_facing;
    CellType m_valBelow;
    int inputMap;
    Bullet* m_shot;
    std::pair<int, int> m_spawnPoint;
    int m_lives;
    bool m_alive;
    bool m_hasSpecialBullet = false; // Indică dacă jucătorul are glonțul special
    PowerUpType m_powerUp;
};