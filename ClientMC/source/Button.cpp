#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& text)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_text(text), m_buttonTexture(nullptr) {}


void Button::Render(SDL_Renderer* renderer, TTF_Font* font) {
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Alb pentru contur

    // Desen?m dreptunghiul cu contur (f?r? umplutur?)
    SDL_Rect buttonRect = { m_x, m_y, m_width, m_height };
    SDL_RenderDrawRect(renderer, &buttonRect); // Desen?m întregul dreptunghi cu contur

    // Restabilim culoarea original? a renderer-ului
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // Desen?m textul în interiorul butonului
    SDL_Color textColor = { 255, 255, 255 };  // Culoare alb? pentru text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, m_text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface!" << std::endl;
        return;
    }

    // Cre?m textura pentru textul butonului
    if (m_buttonTexture != nullptr) {
        SDL_DestroyTexture(m_buttonTexture);  // Dac? exist? deja o textur?, o eliber?m
    }
    m_buttonTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
   // SDL_FreeSurface(textSurface);

    // Calcul?m pozi?ia textului pentru a-l centra în buton
    SDL_Rect textRect = { m_x + (m_width - textSurface->w) / 2, m_y + (m_height - textSurface->h) / 2,
                          textSurface->w, textSurface->h };

    // Desen?m textul pe ecran
    SDL_RenderCopy(renderer, m_buttonTexture, nullptr, &textRect);
}



// Verific? dac? butonul a fost ap?sat
bool Button::IsClicked(int mouseX, int mouseY) {
    return mouseX >= m_x && mouseX <= m_x + m_width && mouseY >= m_y && mouseY <= m_y + m_height;
}
