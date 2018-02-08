#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameObject : public sf::Drawable, protected sf::Transformable
{
public:
	GameObject();
	void SetPosition(const sf::Vector3f& position);
	const sf::Vector3f& GetPosition() { return m_Position; }

private:
	friend class GameObjectComparator;

	sf::Vector3f m_Position;
	static unsigned int g_Id;
	unsigned int m_Id;
};
