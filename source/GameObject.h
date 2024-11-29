#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include <string>

class Game;

class GameObject
{
public:
	GameObject(int X, int Y);
	GameObject(Vector2D pos);
	virtual ~GameObject() = default;

	//virtual void draw();
	virtual void Update(Game* game);
	virtual void Clean();

	Vector2D& getPos();

protected:
	Vector2D m_pos, m_vel;
};