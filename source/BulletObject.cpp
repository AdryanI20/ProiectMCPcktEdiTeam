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
        case BOMB_WALL: {
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
            map->setPositionValue(m_pos.getX(), m_pos.getY(), CellType::FREE_SPACE);

            explodeBombWall(game, newPos);

            /*int centerX = newPos.getX();
            int centerY = newPos.getY();
            for (int offsetY = -1; offsetY <= 1; offsetY++)
            {
                for (int offsetX = -1; offsetX <= 1; offsetX++)
                {
                    int neighborY = centerY + offsetY;
                    int neighborX = centerX + offsetX;
                    if (neighborX >= 0 && neighborX < map->getSize().first &&
                        neighborY >= 0 && neighborY < map->getSize().second) {

                        if (map->getPositionValue(neighborX, neighborY) == CellType::DESTRUCTIBIL_WALL) {
                            map->setPositionValue(neighborX, neighborY, CellType::FREE_SPACE);
                        }
                    }
                    
                }
            }*/

            Clean();
            break;
        }
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

void Bullet::explodeBombWall(Game* game, Vector2D pos)
{
    Map* map = game->getMap();

    for (int offsetY = -1; offsetY <= 1; offsetY++)
    {
        for (int offsetX = -1; offsetX <= 1; offsetX++)
        {
            if (offsetX != 0 || offsetY != 0)
            {
                int neighborY = pos.getY() + offsetY;
                int neighborX = pos.getX() + offsetX;

                if (neighborX >= 0 && neighborX < map->getSize().first &&
                    neighborY >= 0 && neighborY < map->getSize().second) {

                    switch (map->getPositionValue(neighborX, neighborY))
                    {
                    case DESTRUCTIBIL_WALL:
                    case PLAYER:
                        map->setPositionValue(neighborX, neighborY, CellType::FREE_SPACE);
                        Clean();
                        break;
                    case BOMB_WALL:
                        map->setPositionValue(neighborX, neighborY, CellType::FREE_SPACE);
                        Vector2D bombWallPos = Vector2D(neighborX, neighborY);
                        explodeBombWall(game, bombWallPos);
                        break;
                    }
                }
            }
        }
    }
}