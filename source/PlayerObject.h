#pragma once

#include "GameObject.h"

class PlayerObject : public GameObject
{
public:
    PlayerObject(int X, int Y);

    void Update(InputHandle* inputhandler) override;
    void Clean() override;
    void setPos(int X, int Y);
private:


};