#pragma once
#include "GameObject.h"
#include "CellType.h"

class Bullet : public GameObject {
public:
    Bullet(Vector2D pos, float speed, Vector2D direction, CellType valBelow, const std::string& TEX_ID);

    void Update(Game* game) override;
    void Clean() override;
    void Draw(TextureManager* textureManager, SDL_Renderer* renderer) override;
    bool shouldDestroy();

    void explodeBombWall(Game* game, Vector2D pos);
private:
    float m_speed; 
    Vector2D m_direction;
    CellType m_valBelow;
    bool m_destroyed;
};


