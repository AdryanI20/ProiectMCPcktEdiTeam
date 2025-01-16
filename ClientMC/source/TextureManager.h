#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
#include <map>
#include <string>
#include <tuple>
//#include "Button.h"

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    bool TextLoad(const std::string& input, const std::string& id, SDL_Renderer* renderer, SDL_Color textColor = SDL_Color{ 255, 255, 255, 255 });
    bool ImageLoad(const std::string& fileName, const std::string& id, SDL_Renderer* renderer);

    void Draw(const std::string& id, int x, int y, double scale, SDL_Renderer* renderer,int angle=0, int w=-1, int h=-1);

    //void DrawButton(const std::string& id, Button& button, SDL_Renderer* renderer);

    void clearFromTextureMap(const std::string& id);

    bool TextureExists(const std::string& id);

private:
    TTF_Font *m_font;
    std::map<std::string, std::tuple<SDL_Texture*, int, int> > m_textureMap;
};