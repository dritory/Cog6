#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameObject : public sf::Drawable, protected sf::Transformable
{
public:
	GameObject();
	void SetPosition(const sf::Vector3f& position);
	const sf::Vector3f& GetPosition() { return m_Position; }
	void setHidden(bool hidden) { m_Hidden = hidden; }
	bool isHidden() { return m_Hidden; }

private:
	friend class GameObjectComparator;

	sf::Vector3f m_Position;
	static unsigned int g_Id;
	unsigned int m_Id;
	bool m_Hidden = false;
};
