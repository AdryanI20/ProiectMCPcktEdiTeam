#pragma once
#include "DatabaseManager.h"
#include "GameObject.h"
#include "CellType.h"
#include "BulletObject.h"
#include "PowerUpType.h"
#include <map>

class PlayerObject : public GameObject {
public:
    PlayerObject(Vector2D spawnPos, const std::string& TEX_ID);

    void Update(Map* map, bool shot, std::map<std::string, GameObject*> gameObjects);
    void Clean() override;
    void setPos(int X, int Y);
    bool hasSpecialBullet() const { return m_hasSpecialBullet; }
    void useSpecialBullet() { m_hasSpecialBullet = false; } // Consumă glonțul special
    void givePowerUp(int powerUp);
    void activatePowerUp(PowerUpType powerUp);
    int getLives();
    bool isAlive();
    std::string getID() override;
    void setLivingState(bool state);
    void AddKillPoints();
    void AddWinPoints();
    void SetScore();
    //void respawn(Map* map);
    //void killed(Map* map);

    Vector2D getFacing();
private:
    Vector2D m_facing;
    Bullet* m_shot;
    Vector2D m_spawnPoint;
    int m_lives;
    bool m_alive;
    bool m_hasSpecialBullet = false; // Indică dacă jucătorul are glonțul special
    PowerUpType m_powerUp;
    int m_fireRate;
    float m_powerUpTimer;

    int m_points;
    int m_finalPosition;
    int m_score;
};