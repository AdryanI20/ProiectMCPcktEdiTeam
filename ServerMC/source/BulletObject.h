#pragma once
#include "GameObject.h"
#include "CellType.h"
#include <memory>
#include <map>

class Map;

class Bullet : public GameObject {
public:
    Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID);

    void Update(Map& map, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects);
    std::string getID() override;

    void CollideLogic(Map& map, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects, Vector2D oldPos, Vector2D newPos);
    void explodeBombWall(Map& map, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects, Vector2D pos);

    // Metodă setter pentru glonț special:
    void setIsSpecial(bool val);

    bool isSpecial() const;

    void setState(bool newState);
    bool getState();

private:
    float m_speed;
    Vector2D m_direction;
    Vector2D m_oldPos;
    bool m_hit;
    bool m_isSpecial;
};
