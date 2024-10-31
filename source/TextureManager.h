#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include <map>
#include <string>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    bool Load(const std::string& input, std::string id, SDL_Renderer* renderer);

    void Draw(const std::string& id, int x, int y, int w, int h, double scale, SDL_Renderer* renderer);

    void drawFrame(std::string id, int x, int y, int w, int h, double scale, int currentRow, int currentFrame, SDL_Renderer* renderer);

    void clearFromTextureMap(const std::string& id);

private:
    TTF_Font *m_font;
    std::map<std::string, SDL_Texture*> m_textureMap;
};