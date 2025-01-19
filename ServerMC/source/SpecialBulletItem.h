#pragma once
#include "GameObject.h"
#include "PlayerObject.h"
#include "Map.h"
#include "CellType.h"
#include <map>
#include <memory>


class SpecialBulletItem : public GameObject {
public:

    SpecialBulletItem(int x, int y, const std::string& textureID = "special_bullet_item");

    void Update(Map& map, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects);

    virtual std::string getID() override;

    bool m_destroy;
};
