#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../Rendering/SpriteBatch.h"

class InteractableEntity;

class EntitySystem : public sf::Drawable
{
public:
	EntitySystem();
	~EntitySystem();

	template<class entity>
	entity* Add(const std::string& strId = std::string());

	template <class entity>
	entity* Get(const EntityId& id);

	template <class entity>
	entity* Get(const std::string& strId);

	Entity* Get(const EntityId& id);

	template <class entity>
	bool Is(const EntityId& id);

	void Update();
	void SetBatcher(SpriteBatch& batcher);
	void RemoveEntity(EntityId entityId);

private:
	friend class InteractableEntity;

	void addInteractable(InteractableEntity* entity);
	void removeInteractable(InteractableEntity* entity);

	void cleanupEntities();

	std::vector<std::unique_ptr<Entity>> m_Entities;
	std::vector<InteractableEntity*> m_Interactables;
	std::unordered_map<std::string, EntityId> m_StringLookup;
	std::queue<EntityId> m_UnusedEntityIds;
	std::queue<EntityId> m_EntitiesToRemove;
	EntityId m_Next;
	SpriteBatch* m_SpriteBatcher;

	EntityId getNextId();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

template <class entity>
entity* EntitySystem::Add(const std::string& strId)
{
	// Assume no errors, for now
	EntityId id = getNextId();

	auto& ent = m_Entities[id];
	ent = std::make_unique<entity>(this, id);;
	if(!strId.empty())
	{
		if(m_StringLookup.find(strId) != m_StringLookup.end())
		{
			std::cout << "Entity with id: \"" << strId << "\ is already exists, ignoring" << std::endl;
		}
		else
		{
			m_StringLookup[strId] = id;
		}
	}

	ent->Load();
	
	return static_cast<entity*>(ent.get());
}

template <class entity>
entity* EntitySystem::Get(const EntityId& id)
{
	if(!Is<entity>(id))
	{
		std::cout << "Tried to fetch entity of type != to requested type" << std::endl;
		return nullptr;
	}

	return static_cast<entity*>(Get(id));
}

template <class entity>
entity* EntitySystem::Get(const std::string& strId)
{
	if(m_StringLookup.find(strId) == m_StringLookup.end())
	{
		std::cout << "Tried to get entity that does not exist in lookup" << std::endl;
		return nullptr;
	}
	return Get<entity>(m_StringLookup[strId]);
}

template <class entity>
bool EntitySystem::Is(const EntityId& id)
{
	return id < m_Entities.size() && m_Entities[id] && typeid(*m_Entities[id].get()) == typeid(entity);
}

// Template entity functions

template <class entity>
bool Entity::Is()
{
	return m_System->Is<entity>(m_Id);
}