#include "ButtonObject.h"

ButtonObject::ButtonObject(Vector2D pos, Vector2D size, int scale, int type, std::string message, const std::string& TEX_ID) : GameObject(pos, TEX_ID), m_size(size), m_scale(scale), m_type(type), m_textID(message), m_held(false), m_wasHeld(false), m_specialFlag(false), m_btnColor(SDL_Color{ 255,255,255,255 }), m_newText(" "), m_oldText(" ") {}

void ButtonObject::Update(Game* game) {

    switch (m_type)
    {
    case 0: {//Play button
        InputHandle* inputHandler = game->getInputHandler();
        Vector2D* mousePos = inputHandler->getMousePos();
        bool mouseInBtn = IsPointInsideRect(*mousePos, m_pos, m_size);
        if (mouseInBtn)
            m_btnColor = SDL_Color{ 200, 0, 0, 255 };
        else
            m_btnColor = SDL_Color{ 255, 255, 255, 255 };

        if (mouseInBtn && inputHandler->getMouseButtonState(0)) {
            m_held = true;
        }
        else {
            if (m_held == true)
                m_wasHeld = true;
            m_held = false;
        }

        if (m_wasHeld) {
            m_wasHeld = false;
            if (JoinGame(game)) {
                m_specialFlag = true;
            }
            else {
                std::cerr << "Couldn't join game" << std::endl;
            }
        }
    }
        break;
    case 1: { //Server button
        InputHandle* inputHandler = game->getInputHandler();
        Vector2D* mousePos = inputHandler->getMousePos();
        bool mouseInBtn = IsPointInsideRect(*mousePos, m_pos, m_size);
        if (mouseInBtn) {
            m_btnColor = SDL_Color{ 200, 0, 0, 255 };
            if (SDL_IsTextInputActive() == SDL_FALSE)
                SDL_StartTextInput();
            std::string tempInput = inputHandler->getTextInput();
            m_oldText = m_newText;
            m_newText = tempInput.empty() == true ? " " : tempInput;
        } else {
            if (SDL_IsTextInputActive() == SDL_TRUE)
                SDL_StopTextInput();
            m_btnColor = SDL_Color{ 255, 255, 255, 255 };
        }
    }
        break;
    }

}

bool ButtonObject::JoinGame(Game* game) {
    cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:18080/join_game" });
    if (r.status_code == 200) {
        auto json = crow::json::load(r.text);
        game->setclientID(json["clientID"].i());
        return true;
    }
    return false;
}

bool ButtonObject::IsPointInsideRect(const Vector2D point, Vector2D rectPos, Vector2D rectSize) {
    rectPos *= m_scale;
    rectSize *= m_scale;
    return (
        point.getX() >= rectPos.getX() &&
        point.getY() >= rectPos.getY() &&
        point.getX() <= rectPos.getX() + rectSize.getX() &&
        point.getY() <= rectPos.getY() + rectSize.getY()
        );
}

void ButtonObject::DrawUnfilledRectangle(SDL_Renderer* renderer, int thickness, SDL_Color color, SDL_Color oldColor) {
    SDL_Rect rect;
    rect.x = m_pos.getX() * m_scale;
    rect.y = m_pos.getY() * m_scale;
    rect.w = m_size.getX() * m_scale;
    rect.h = m_size.getY() * m_scale;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Top line
    SDL_Rect topLine = { rect.x, rect.y, rect.w, thickness };
    SDL_RenderFillRect(renderer, &topLine);

    // Bottom line
    SDL_Rect bottomLine = { rect.x, rect.y + rect.h - thickness, rect.w, thickness };
    SDL_RenderFillRect(renderer, &bottomLine);

    // Left line
    SDL_Rect leftLine = { rect.x, rect.y, thickness, rect.h };
    SDL_RenderFillRect(renderer, &leftLine);

    // Right line
    SDL_Rect rightLine = { rect.x + rect.w - thickness, rect.y, thickness, rect.h };
    SDL_RenderFillRect(renderer, &rightLine);

    SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, 255);
}

void ButtonObject::Draw(TextureManager* textureManager, SDL_Renderer* renderer) {
	switch (m_type)
	{
    case 0: {//Play button
        DrawUnfilledRectangle(renderer, 10, m_btnColor, SDL_Color{ 30,30,30,255 });
        if (textureManager->TextureExists(m_textID))
            textureManager->Draw(m_textID, (m_pos.getX()) * m_scale, (m_pos.getY() + m_size.getY() / 4) * m_scale, m_scale, renderer);
    }
        break;
    case 1: { //Server button
        DrawUnfilledRectangle(renderer, 10, m_btnColor, SDL_Color{ 30,30,30,255 });
        if (m_oldText != m_newText) {
            textureManager->clearFromTextureMap(m_textID);
            textureManager->TextLoad(m_newText, m_textID, renderer);
        }
        if (textureManager->TextureExists(m_textID))
            textureManager->Draw(m_textID, (m_pos.getX()) * m_scale, (m_pos.getY() + m_size.getY() / 2) * m_scale, m_scale/2, renderer);
    }
        break;
	}
}

void ButtonObject::Clean() {

}

bool ButtonObject::getFlag()
{
    return m_specialFlag;
}
