#pragma once
#include "Vector2D.h"
#include <string>
#include "Game.h"

class GameObject
{
public:
	GameObject(Vector2D pos, const std::string& TEX_ID = "");
	virtual ~GameObject() = default;

	virtual void Update(Game* game);
	virtual void Clean();
	virtual void Draw(TextureManager* textureManager, SDL_Renderer* renderer);
	virtual std::string getID() { return m_textureID; }

	Vector2D& getPos();

	Vector2D& getVel();
	void setVel(Vector2D newVel);

protected:
	Vector2D m_pos, m_vel;
	std::string m_textureID;
};