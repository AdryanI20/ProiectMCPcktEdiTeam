#include "GameObject.h"

GameObject::GameObject(Vector2D pos, const std::string& TEX_ID) : m_pos(pos), m_vel(0, 0), m_textureID(TEX_ID) {}

Vector2D& GameObject::getPos() {
	return m_pos;
}

Vector2D& GameObject::getVel()
{
	return m_vel;
}

void GameObject::setVel(Vector2D newVel)
{
	m_vel = newVel;
}

void GameObject::Update(Game* game) {}

void GameObject::Clean() {}

void GameObject::Draw(TextureManager* textureManager, SDL_Renderer* renderer) {}