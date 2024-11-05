#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include <map>
#include <string>
#include <tuple>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    bool Load(const std::string& input, std::string id, SDL_Renderer* renderer);

    void Draw(const std::string& id, int x, int y, double scale, SDL_Renderer* renderer, int w=-1, int h=-1);

//    void drawFrame(std::string id, int x, int y, int w, int h, double scale, int currentRow, int currentFrame, SDL_Renderer* renderer);

    void clearFromTextureMap(const std::string& id);

    bool TextureExists(const std::string& id);

private:
    TTF_Font *m_font;
    std::map<std::string, std::tuple<SDL_Texture*, int, int> > m_textureMap;
};