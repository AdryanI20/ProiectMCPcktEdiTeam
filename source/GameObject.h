#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include <string>

class Game;

class GameObject
{
public:
	GameObject(int X, int Y);

	//virtual void draw();
	virtual void Update(Game* game);
	virtual void Clean();

	Vector2D& getPos();

protected:
	virtual ~GameObject() = default;
	Vector2D m_pos, m_vel;
};