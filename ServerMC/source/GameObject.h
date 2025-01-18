#pragma once
#include "Vector2D.h"
#include <string>

class Game;
class TextureManager;
struct SDL_Renderer;

class GameObject
{
public:
	GameObject(int X, int Y, const std::string& TEX_ID="");
	GameObject(Vector2D pos, const std::string& TEX_ID = "");
	virtual ~GameObject() = default;

	virtual std::string getID() { return m_textureID; }

	Vector2D& getPos();

	Vector2D& getVel();
	void setVel(Vector2D newVel);

protected:
	Vector2D m_pos, m_vel;
	std::string m_textureID;
};