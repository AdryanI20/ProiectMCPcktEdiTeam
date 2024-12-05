#pragma once
#include "GameObject.h"
#include "CellType.h"

class Map;

class Bullet : public GameObject {
public:
    Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID);

    void Update(Game* game) override;
    void Clean() override;
    void Draw(TextureManager* textureManager, SDL_Renderer* renderer) override;
    bool shouldDestroy();

    void CollideLogic(Map* map, Vector2D oldPos, Vector2D newPos);

    Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID, bool isSpecial = false)
        : GameObject(pos, TEX_ID), m_speed(speed), m_direction(direction), m_destroyed(false), m_oldPos(pos), m_isSpecial(isSpecial) {
        m_vel = m_direction * m_speed;
    }

    bool isSpecial() const { return m_isSpecial; }


private:
    void explodeBombWall(Map* map, Vector2D pos);
    float m_speed; 
    Vector2D m_direction;
    bool m_destroyed;
    Vector2D m_oldPos;

    bool m_isSpecial = false; // Dacă este un glonț special
};



