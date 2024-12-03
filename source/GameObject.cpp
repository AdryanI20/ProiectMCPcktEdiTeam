#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(int X, int Y, const std::string& TEX_ID) : m_pos(X, Y), m_vel(0, 0), m_textureID(TEX_ID) {}

GameObject::GameObject(Vector2D pos, const std::string& TEX_ID) : m_pos(pos), m_vel(0, 0), m_textureID(TEX_ID) {}

Vector2D& GameObject::getPos() {
	return m_pos;
}

void GameObject::Draw(TextureManager* textureManager, SDL_Renderer* renderer) {}

void GameObject::Update(Game* game) {}

void GameObject::Clean() {}