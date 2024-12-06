#pragma once
#include "GameObject.h"
#include "CellType.h"
#include "BulletObject.h"

class PlayerObject : public GameObject {
public:
    PlayerObject(int X, int Y, CellType valBelow, int mapping, const std::string& TEX_ID);

    void Update(Game* game) override;
    void Clean() override;
    void Draw(TextureManager* textureManager, SDL_Renderer* renderer) override;
    void setPos(int X, int Y);
    bool hasSpecialBullet() const { return m_hasSpecialBullet; }
    void useSpecialBullet() { m_hasSpecialBullet = false; } // Consumă glonțul special

    int getLives();
    bool isAlive();
    void setLivingState(bool state);
    void decreaseLives();
private:
    Vector2D m_facing;
    CellType m_valBelow;
    int inputMap;
    Bullet* m_shot;
    std::pair<int, int> m_spawnPoint;
    int m_lives;
    bool m_alive;
    bool m_hasSpecialBullet = false; // Indică dacă jucătorul are glonțul special
};