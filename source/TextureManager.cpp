#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

bool TextureManager::Load(const std::string& input, std::string id, SDL_Renderer* renderer)
{
    m_font = TTF_OpenFont("../resources/kongtext.ttf", 24);
    if (!m_font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Surface* text_surf = TTF_RenderText_Solid(m_font, input.c_str(), SDL_Color( 255, 255, 255, 255));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surf);
    std::cout << text_surf->w << " " << text_surf->h << std::endl;
    SDL_FreeSurface(text_surf);

    if (texture == nullptr) {
        std::cout << "Could not create texture from surface!!!" << std::endl;
        return false;
    }

    m_textureMap[id] = texture;
    return true;
}

void TextureManager::Draw(const std::string& id, int x, int y, int w, int h, double scale, SDL_Renderer* renderer) {
    SDL_Rect srcRect, destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;
    destRect.w *= scale;
    destRect.h *= scale;

    SDL_RenderCopy(renderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::clearFromTextureMap(const std::string& id)
{
    m_textureMap.erase(id);
}