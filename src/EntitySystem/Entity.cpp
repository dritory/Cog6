#include "Entity.h"
#include "../AssetLoader/AssetLoader.h"

Entity::Entity(EntitySystem* system, const EntityId& id) : m_Id(id), m_Health(0), m_System(system)
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
	std::string asset = "entities/" + GetSpriteLocation();
	sf::Texture* tex = AssetLoader<sf::Texture>::GetInstance().Get(asset);
	if(tex == nullptr)
	{
		AssetLoader<sf::Texture>::GetInstance().LoadAsset(asset);
		tex = AssetLoader<sf::Texture>::GetInstance().Get(asset);
	}
	
	m_Sprite.setTexture(*tex);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Sprite, states);
}
