#include "BulletObject.h"
#include <cmath>
#include "PlayerObject.h"
#include "Map.h"

Bullet::Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID)
    : GameObject(pos, TEX_ID), m_speed(speed), m_direction(direction), m_hit(false), m_oldPos(pos), m_isSpecial(false)
{
    m_vel = m_direction * m_speed;
}

void Bullet::Update(Map& map, std::map<std::string, std::shared_ptr<GameObject> >& gameObjects) {
    if (m_hit == true) return;

    m_oldPos = Vector2D(round(m_pos.getX()), round(m_pos.getY()));
    m_pos += m_vel;
    Vector2D newPos(round(m_pos.getX()), round(m_pos.getY()));

    if (newPos == m_oldPos) return;

    CollideLogic(map, gameObjects, m_oldPos, newPos);

    m_oldPos = newPos;
}

void Bullet::explodeBombWall(Map& map, std::map<std::string, std::shared_ptr<GameObject> >& gameObjects, Vector2D pos) {
    if (m_hit == true) return;

    map.setPositionValue(pos.getX(), pos.getY(), FREE_SPACE);
    for (int offsetY = -6; offsetY <= 6; offsetY++)
    {
        for (int offsetX = -6; offsetX <= 6; offsetX++)
        {
            if (offsetX != 0 || offsetY != 0)
            {
                int neighborY = pos.getY() + offsetY;
                int neighborX = pos.getX() + offsetX;
                std::pair<int, int> mapSize = map.getSize();
                if (neighborX >= 0 && neighborX < mapSize.first &&
                    neighborY >= 0 && neighborY < mapSize.second) {

                    Vector2D neighborPos(neighborX, neighborY);
                    for (const auto& [_, object] : gameObjects) {
                        if (object->getPos() == neighborPos) {
                            if (std::shared_ptr<PlayerObject> plrObj = std::dynamic_pointer_cast<PlayerObject>(object)) {
                                plrObj->Respawn();
                            }
                            else if (std::shared_ptr<Bullet> BltObj = std::dynamic_pointer_cast<Bullet>(object)) {
                                BltObj->setState(true);
                            }
                            break;
                        }
                    }

                    switch (map.getPositionValue(neighborX, neighborY))
                    {
                    case DESTRUCTIBIL_WALL:
                        map.setPositionValue(neighborX, neighborY, FREE_SPACE);
                        break;
                    case BOMB_WALL:
                        map.setPositionValue(neighborX, neighborY, FREE_SPACE);
                        explodeBombWall(map, gameObjects, neighborPos);
                        break;
                    }
                }
            }
        }
    }
}


void Bullet::CollideLogic(Map& map, std::map<std::string, std::shared_ptr<GameObject> >& gameObjects, Vector2D oldPos, Vector2D newPos) {
    if (m_hit == true) return;

    for (const auto& [_, object] : gameObjects) {
        if (object->getPos() == newPos) {
            if (std::shared_ptr<PlayerObject> plrObj = std::dynamic_pointer_cast<PlayerObject>(object)) {
                //TODO: TRACK WHOSE THE ONE WHO SHOT THE BULLET TO AWARD KILL
                plrObj->Respawn();
                m_hit = true;
            }
            else {
                std::shared_ptr<Bullet> bltObj = std::dynamic_pointer_cast<Bullet>(object);
                if (bltObj && bltObj.get() != this) {
                    bltObj->setState(true);
                    m_hit = true;
                }
            }
            break;
        }
    }

    switch (map.getPositionValue(newPos.getX(), newPos.getY()))
    {
    case FREE_SPACE:
        m_pos = newPos;
        break;
    case DESTRUCTIBIL_WALL:
        map.setPositionValue(newPos.getX(), newPos.getY(), FREE_SPACE);
        m_hit = true;
        break;
    case INDESTRUCTIBIL_WALL:
        if (m_isSpecial) map.setPositionValue(newPos.getX(), newPos.getY(), FREE_SPACE);
        m_hit = true;
        break;
    case BOMB_WALL: {
        explodeBombWall(map, gameObjects, newPos);
        m_hit = true;
        break;
    }
    case EMPTY_SPACE:
        m_hit = true;
        break;
    }
}

bool Bullet::isSpecial() const {
    return m_isSpecial; 
}

void Bullet::setState(bool newState)
{
    m_hit = newState;
}

bool Bullet::getState()
{
    return m_hit;
}

std::string Bullet::getID()
{
    return m_textureID;
}
void Bullet::setIsSpecial(bool val)
{
    m_isSpecial = val;
}
