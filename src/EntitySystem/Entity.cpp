#include "Entity.h"
#include "../AssetLoader/AssetLoader.h"
#include "..\PlayState.h"

Entity::Entity(EntitySystem* system, const EntityId& id) : m_Id(id), m_Health(10), m_System(system) {
}

Entity::~Entity() = default;




void Entity::FixedUpdate(sf::Time elapsed) {
	
	float health = (float)GetHealth();
	if(maxHealth > 0 && health != m_lastHealth) {
		
		if (health == 0) {

			//tileSystem->pathfinder->recalculateMap();
			//GetSystem()->RemoveEntity(this);
		}
		else {
			if (health < ((float)maxHealth / 100) * 30) {
				healthBar.setFillColor(sf::Color::Red);
			}
			else if (health < ((float)maxHealth / 100) * 60) {
				healthBar.setFillColor(sf::Color(150, 150, 10));
			}
			else {
				healthBar.setFillColor(sf::Color::White);
			}
			
			healthBar.setSize(sf::Vector2f(10.0f * (((1.0f / (float)maxHealth) * (float)GetHealth())), 2.0f));
		}
	}
	m_lastHealth = health;
}
void Entity::Update() {
}
void Entity::setColor(const sf::Color &color)
{
	this->m_color = color;
	m_Sprite.setColor(color);
}
const sf::Color & Entity::getColor()
{
	return m_color;
}
void Entity::Load(const std::string &spriteLocation) {
	
		healthBar.setSize(sf::Vector2f(10, 2));

		std::string sprite = (spriteLocation != std::string() ? spriteLocation : GetSpriteLocation());
		if (sprite != "") {
			std::string asset = "entities/" + sprite;

			sf::Texture* tex = AssetLoader<sf::Texture>::GetInstance().Get(asset);
			if (tex == nullptr) {
				AssetLoader<sf::Texture>::GetInstance().LoadAsset(asset);
				tex = AssetLoader<sf::Texture>::GetInstance().Get(asset);
			}

			m_Sprite.setTexture(*tex);
		}
}

static sf::Texture getTexture(std::string loc) {
	sf::Texture tex;
	tex.loadFromFile("assets/entities/" + loc);
	return tex;
}
void Entity::SetHealthToMax() {
	m_Health = maxHealth;
}
void Entity::SetPosition(const sf::Vector3f & position) {
	if (maxHealth > 0) {
		int size = Game::Instance()->tileSystem->getTileSize();
		sf::Vector3f bar(2 * size / 3, -10, 0);
		sf::Vector2f pos = Game::Instance()->tileSystem->isoToWorldCoord((position + bar));
		healthBar.setPosition(pos);
	}
	GameObject::SetPosition(position);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(m_Sprite, states);

}

void Entity::drawGUI(sf::RenderTarget & target, sf::RenderStates states) const {
	if (maxHealth > 0 && GetHealth() < maxHealth) {
		target.draw(healthBar, states);
	}
}
