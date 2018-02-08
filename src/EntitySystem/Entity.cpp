#include "Entity.h"

Entity::Entity(EntitySystem* system) : m_Id(0), m_Health(0), m_System(system)
{
}

Entity::~Entity() = default;

static sf::Texture getTexture(std::string loc)
{
	sf::Texture tex;
	tex.loadFromFile("assets/entities/" + loc);
	return tex;
}

void Entity::Load()
{
	static sf::Texture tex = getTexture(GetSpriteLocation());
	
	m_Sprite.setTexture(tex);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Sprite, states);
}
