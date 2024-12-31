#pragma once
#include "GameObject.h"
#include "CellType.h"

class Map;

class Bullet : public GameObject {
public:
    Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID);

    void Update() override;
    std::string getID() override;
    void Clean() override;
    bool shouldDestroy();

    //void CollideLogic(Map* map, Vector2D oldPos, Vector2D newPos, Game* game);
    
    bool isSpecial() const;
    //void explodeBombWall(Map* map, Vector2D pos);

private:
    //void KillPlayer(Game* game, Vector2D pos);
    float m_speed; 
    Vector2D m_direction;
    bool m_destroyed;
    Vector2D m_oldPos;

    bool m_isSpecial;
};



