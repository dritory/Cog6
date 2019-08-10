#pragma once

#include <SFML/Graphics.hpp>
struct ObjectState {
	float x, y, z;
	float vx, vy, vz; //velocity

	unsigned int id;
};

class GameObject : public sf::Drawable, protected sf::Transformable
{
public:
	GameObject();
	virtual void SetPosition(const sf::Vector3f& position);
	const sf::Vector3f& GetPosition() { return m_Position; }
	void setHidden(bool hidden) { m_Hidden = hidden; }
	bool isHidden() { return m_Hidden; }

	virtual void pushState(ObjectState &state);
	unsigned int getID() {
		return m_Id;
	};

private:
	friend class GameObjectComparator;

	sf::Vector3f m_Position;
	static unsigned int g_Id;
	unsigned int m_Id;
	bool m_Hidden = false;
};
