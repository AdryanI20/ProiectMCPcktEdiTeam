#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
    for (auto const& [key, _] : m_textureMap)
        clearFromTextureMap(key);
}

bool TextureManager::Load(const std::string& input, const std::string& id, SDL_Renderer* renderer)
{
    m_font = TTF_OpenFont("resources/kongtext.ttf", 24);
    if (!m_font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Surface* text_surf = TTF_RenderText_Solid_Wrapped(m_font, input.c_str(), SDL_Color( 255, 255, 255, 255), 960);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surf);
    int textW = text_surf->w;
    int textH = text_surf->h;

    SDL_FreeSurface(text_surf);

    if (texture == nullptr) {
        std::cout << "Could not create texture from surface!!!" << std::endl;
        return false;
    }

    m_textureMap[id] = std::make_tuple(texture, textW, textH);
    return true;
}

void TextureManager::Draw(const std::string& id, int x, int y, double scale, SDL_Renderer* renderer, int w, int h) {
    SDL_Rect srcRect, destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    if (w == -1 or h == -1) {
        srcRect.w = destRect.w = std::get<1>(m_textureMap[id]);
        srcRect.h = destRect.h = std::get<2>(m_textureMap[id]);
    } else {
        srcRect.w = destRect.w = w;
        srcRect.h = destRect.h = h;
    }
    destRect.x = x;
    destRect.y = y;
    destRect.w *= scale;
    destRect.h *= scale;

    SDL_RenderCopy(renderer, std::get<0>(m_textureMap[id]), &srcRect, &destRect);
}

void TextureManager::clearFromTextureMap(const std::string& id)
{
    m_textureMap.erase(id);
}

bool TextureManager::TextureExists(const std::string &id) {
    return (m_textureMap.find(id) != m_textureMap.end());
}
