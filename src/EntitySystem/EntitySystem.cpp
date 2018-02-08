#include "EntitySystem.h"



EntitySystem::EntitySystem(): m_Next(0), m_SpriteBatcher(nullptr)
{
}


EntitySystem::~EntitySystem() = default;

Entity* EntitySystem::Get(const EntityId& id)
{
	if (id >= m_Entities.size() || !m_Entities[id])
	{
		std::cout << "Tried to fetch entity that did not exist" << std::endl;
		return nullptr;
	}

	return m_Entities[id].get();
}

void EntitySystem::Update()
{
	for (auto& it : m_Entities)
		it->Update();
}

void EntitySystem::SetBatcher(SpriteBatch& batcher)
{
	m_SpriteBatcher = &batcher;
}

EntityId EntitySystem::getNextId()
{
	EntityId id = !m_UnusedEntityIds.empty() ? m_UnusedEntityIds.front() : m_Next++;
	if (!m_UnusedEntityIds.empty())m_UnusedEntityIds.pop();

	if (id + 1 > m_Entities.size()) m_Entities.resize(id + 1);
	return id;
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_SpriteBatcher == nullptr)
	{
		for (const auto& it : m_Entities)
			target.draw(*it, states);
	}
	else
	{
		for (const auto& it : m_Entities)
		{
			m_SpriteBatcher->QueueObject(it.get());
		}
	}
}
