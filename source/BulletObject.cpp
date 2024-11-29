#include "BulletObject.h"
#include <cmath>
#include "Game.h"

Bullet::Bullet(Vector2D pos, float speed, Vector2D direction, CellType valBelow)
    : GameObject(pos), m_speed(speed), m_direction(direction), m_valBelow(valBelow), m_destroyed(false) {}
//TODO: IF BULLET IS SPAWNED INSIDE OF AN OBJECT APPLY THE RELEVANT LOGIC

void Bullet::Update(Game* game) {
    Map* map = game->getMap();

    m_vel += m_direction * m_speed;

    Vector2D newPos = Vector2D(round((m_pos + m_vel).getX()), round((m_pos + m_vel).getY()));

    if (newPos != m_pos) {
        m_vel = Vector2D(0, 0);
        switch (map->getPositionValue(newPos.getX(), newPos.getY()) )
        {
        case FREE_SPACE:
            map->setPositionValue(m_pos.getX(), m_pos.getY(), m_valBelow);
            m_valBelow = map->getPositionValue(m_pos.getX(), m_pos.getY());
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::BULLET);
            m_pos = newPos;
            break;
        case DESTRUCTIBIL_WALL:
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        case INDESTRUCTIBIL_WALL:
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        case BOMB_WALL:
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        case BULLET:
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        case PLAYER:
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        case VOID:
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);
            Clean();
            break;
        }
    }

}

void Bullet::Clean() {
    m_destroyed = true;
}

bool Bullet::shouldDestroy()
{
    return m_destroyed;
}
