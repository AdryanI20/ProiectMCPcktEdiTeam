#pragma once

#include "GameObject.h"

class ButtonObject : public GameObject {
public:
    ButtonObject(Vector2D pos, Vector2D size, int scale, int type, std::string message, const std::string& TEX_ID, int inputIndex = 0);

    void Update(Game* game) override;
    void Draw(TextureManager* textureManager, SDL_Renderer* renderer) override;
    void Clean() override;

    bool getFlag();
    std::string getText();

private:
    Vector2D m_size;
    int m_scale;
    int m_type;
    std::string m_textID;
    std::string m_oldText;
    std::string m_newText;
    bool m_held;
    bool m_wasHeld;
    bool m_specialFlag;
    SDL_Color m_btnColor;
    int m_inputIndex;

    void DrawUnfilledRectangle(SDL_Renderer* renderer, int thickness, SDL_Color color, SDL_Color oldColor);
    bool IsPointInsideRect(const Vector2D point, Vector2D rectPos, Vector2D rectSize);
    bool JoinGame(Game* game);
};
