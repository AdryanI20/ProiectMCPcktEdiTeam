#include "SpecialBulletItem.h"
#include "PlayerObject.h"

SpecialBulletItem::SpecialBulletItem(int x, int y, const std::string& textureID)
        : GameObject(x, y, textureID), m_destroy(false)
{
}

void SpecialBulletItem::Update(Map& map, std::map<std::string, std::shared_ptr<GameObject>>& gameObjects)
{

    for (auto& [objID, obj] : gameObjects) {
        std::shared_ptr<PlayerObject> player = std::dynamic_pointer_cast<PlayerObject>(obj);
        if (player && player->getPos() == this->getPos()) {

            player->setHasSpecialBullet(true);

            map.setPositionValue((int)getPos().getX(), (int)getPos().getY(), CellType::FREE_SPACE);

            m_destroy = true;
            break;
        }
    }
}

std::string SpecialBulletItem::getID()
{
    return m_textureID;
}
