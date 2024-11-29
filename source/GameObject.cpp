#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(int X, int Y) : m_pos(X, Y), m_vel(0, 0) {}

Vector2D& GameObject::getPos() {
	return m_pos;
}

void GameObject::Update(Game* game) {

}

void GameObject::Clean() {

}