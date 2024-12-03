#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include <string>

class Game;
class TextureManager;
class SDL_Renderer;

class GameObject
{
public:
	GameObject(int X, int Y, const std::string& TEX_ID="");
	GameObject(Vector2D pos, const std::string& TEX_ID = "");
	virtual ~GameObject() = default;

	virtual void Draw(TextureManager* textureManager, SDL_Renderer* renderer);
	virtual void Update(Game* game);
	virtual void Clean();

	Vector2D& getPos();

protected:
	Vector2D m_pos, m_vel;
	std::string m_textureID;
};