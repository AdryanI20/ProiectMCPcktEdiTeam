#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Button {
public:
    Button(int x, int y, int width, int height, const std::string& text);
    void Render(SDL_Renderer* renderer, TTF_Font* font);
    bool IsClicked(int mouseX, int mouseY);

    // Metoda de returnare a texturii butonului
    SDL_Texture* GetTexture() const { return m_buttonTexture; }

private:
    int m_x, m_y, m_width, m_height;
    std::string m_text;
    SDL_Texture* m_buttonTexture = nullptr;  // Membru pentru textura butonului
};

#endif
