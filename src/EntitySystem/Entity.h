#pragma once

#include <SFML/Graphics.hpp>
#include "../GameObject.h"

typedef unsigned int EntityId;

class EntitySystem;

class Entity : public GameObject
{
public:
	Entity(EntitySystem* system);
	~Entity();

	EntityId GetId() { return m_Id; }

	template<class entity>
	bool Is();

protected:
	virtual void Update() = 0;

	virtual std::string GetSpriteLocation() = 0;

private:
	friend class EntitySystem;

	EntityId m_Id;
	int m_Health;

	EntitySystem* m_System;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	void Load();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

