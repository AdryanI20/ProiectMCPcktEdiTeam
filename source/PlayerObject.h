#pragma once
#include "GameObject.h"
#include "CellType.h"
#include "BulletObject.h"

class PlayerObject : public GameObject {
public:
    PlayerObject(int X, int Y, CellType valBelow, int mapping);

    void Update(Game* game) override;
    void Clean() override;
    void setPos(int X, int Y);
private:
    int m_facing;
    CellType m_valBelowPlr;
    int inputMap;
    //std::vector<Bullet*> shots;
};