#include "Character.h"
#include <string_view>

Character::Character(int id, int team, std::string_view name, int points, int score, std::pair<int, int> startPosition)
{
	m_id = id;
	m_team = team;
}

void Character::rotateLeft()
{
	m_facingDirection--;

	if (m_facingDirection == -1)
		m_facingDirection = 3;
}

void Character::rotateRight()
{
	m_facingDirection++;
	
	if (m_facingDirection == 4)
		m_facingDirection = 0;
}

int Character::getFacingDirection()
{
	return m_facingDirection;
}

void Character::setFacingDirection(int direction)
{
	m_facingDirection = direction;
}

void Character::move(int direcction)
{
	switch (direcction)
	{
	case 0:
		m_position.first--;
		break;
	case 1:
		m_position.second--;
		break;
	case 2:
		m_position.first++;
		break;
	case 3:
		m_position.second++;
		break;
	default:
		break;
	}
}
