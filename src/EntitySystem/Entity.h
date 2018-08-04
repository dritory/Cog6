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
	int GetHealth() const { return m_Health; }
	void SetHealth(int health) { m_Health = health; };
	void SetHealthToMax();

	bool isAlive() {
		return (maxHealth > 0 ? m_Health > 0 : true);
	}
	
	bool Deactivated() { return m_Deactivated; }

	virtual void SetPosition(const sf::Vector3f& position);

	virtual void Reset() {};

protected:
	virtual void FixedUpdate();
	virtual void Update();
	virtual std::string GetSpriteLocation() = 0;

	EntitySystem* GetSystem() const { return m_System; }

	
	int maxHealth = 0;


private:
	friend class EntitySystem;
	
	int m_lastHealth;
	EntityId m_Id;
	int m_Health;

	bool m_Removed = false;
	bool m_Deactivated = false;


	EntitySystem* m_System;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	
	sf::RectangleShape healthBar;



protected:
	virtual void Load() {
		Load(std::string());
	}
	virtual void Load(const std::string& spriteLocation);

	void Remove() { m_Removed = true; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void drawGUI(sf::RenderTarget& target, sf::RenderStates states) const;
};
	

