#include "BulletObject.h"
#include <cmath>
#include "Game.h"

Bullet::Bullet(Vector2D pos, float speed, Vector2D direction, const std::string& TEX_ID)
    : GameObject(pos, TEX_ID), m_speed(speed), m_direction(direction), m_destroyed(false), m_oldPos(pos)
{
    m_vel = m_direction * m_speed;
}

void Bullet::Update(Game* game) {
    if (m_destroyed)
        return;

    Map* map = game->getMap();
    m_oldPos = Vector2D(round(m_pos.getX()), round(m_pos.getY()));
    m_pos += m_vel;
    Vector2D newPos(round(m_pos.getX()), round(m_pos.getY()));

    if (newPos == m_oldPos)
        return;

    CollideLogic(map, m_oldPos, newPos);

    m_oldPos = newPos;
}

void Bullet::Clean() {
    m_destroyed = true;
}

void Bullet::Draw(TextureManager* textureManager, SDL_Renderer* renderer) {
    int img_size = 64;
    textureManager->Draw(m_textureID, m_pos.getY() * img_size, m_pos.getX() * img_size, 1, renderer, 0);
}

bool Bullet::shouldDestroy()
{
    return m_destroyed;
}

void Bullet::explodeBombWall(Map* map, Vector2D pos)
{
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
                        explodeBombWall(map, bombWallPos);
                        break;
                    }
                }
            }
        }
    }
}

void Bullet::CollideLogic(Map* map, Vector2D oldPos, Vector2D newPos) {
    switch (map->getPositionValue(newPos.getX(), newPos.getY()))
    {
    case FREE_SPACE:
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        map->setPositionValue(newPos.getX(), newPos.getY(), CellType::BULLET);
        m_pos = newPos;
        break;
    case DESTRUCTIBIL_WALL:
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
        Clean();
        break;
    case INDESTRUCTIBIL_WALL:
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        if (m_isSpecial) {
            map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE); // Distruge peretele
        }
        Clean();
        break;

    case BOMB_WALL: {
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);

        explodeBombWall(map, newPos);

        Clean();
        break;
    }
    case BULLET:
        // elimina ambele gloanțe
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
        m_destroyed = true;

        //eliminarea glonțului aflat deja la noua poziție
        Bullet* otherBullet = game->getBulletAtPosition(newPos); // returnează glonțul la această poziție
        if (otherBullet) {
            otherBullet->Clean();
        }
        break;
    case PLAYER:
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        map->setPositionValue(newPos.getX(), newPos.getY(), CellType::FREE_SPACE);
        //ASTA FUNCTIONEAZA DAR JUCATORUL ESTE INCA IN MEMORIE
        Clean();
        break;
    case VOID:
        map->setPositionValue(oldPos.getX(), oldPos.getY(), CellType::FREE_SPACE);
        Clean();
        break;
    }
}
