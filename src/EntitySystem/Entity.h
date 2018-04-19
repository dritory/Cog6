#pragma once

#include <SFML/Graphics.hpp>
#include "../GameObject.h"

typedef unsigned int EntityId;

class EntitySystem;

class Entity : public GameObject
{
public:
	Entity(EntitySystem* system, const EntityId& id);
	~Entity();

	EntityId GetId() { return m_Id; }

	template<class entity>
	bool Is();
	bool Removed() const { return m_Removed; }
	int GetHealth() { return m_Health; }
	void SetHealth(int health) { m_Health = health; };

protected:
	virtual void Update() = 0;
	virtual std::string GetSpriteLocation() = 0;

	EntitySystem* GetSystem() const { return m_System; }

private:
	friend class EntitySystem;

	EntityId m_Id;
	int m_Health;
	bool m_Removed = false;

	EntitySystem* m_System;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	void Load();
	void Remove() { m_Removed = true; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

