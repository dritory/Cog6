#include "EntitySystem.h"
#include "InteractableEntity.h"


EntitySystem::EntitySystem() : m_Next(0), m_SpriteBatcher(nullptr) {
}


EntitySystem::~EntitySystem() = default;

Entity* EntitySystem::Get(const EntityId& id) {
	if (id >= m_Entities.size() || !m_Entities[id]) {
		std::cout << "Tried to fetch entity that did not exist" << std::endl;
		return nullptr;
	}

	return m_Entities[id].get();
}
void EntitySystem::FixedUpdate(sf::Time elapsed) {
	for (auto& it : m_Entities)
		if (it != nullptr && !it->Deactivated())
			it->FixedUpdate();

	cleanupEntities();
}
void EntitySystem::Update(sf::Time elapsed) {
	for (auto& it : m_Entities)
		if (it != nullptr && !it->Deactivated())
			it->Update();

	for (auto it = m_Interactables.begin(); it < m_Interactables.end(); ++it) {
		auto intr = *it;
		auto ent = (Entity*)intr;
		for (auto it2 = it + 1; it2 < m_Interactables.end(); ++it2) {
			auto intr2 = *it2;
			auto ent2 = (Entity*)intr2;
			if (intr->CanInteract(ent2))
				intr->Interact(ent2);
			if (intr2->CanInteract(ent))
				intr2->Interact(ent);
		}
	}
}

void EntitySystem::SetBatcher(SpriteBatch& batcher) {
	m_SpriteBatcher = &batcher;
}


void EntitySystem::RemoveEntity(EntityId entityId) {
	auto ent = Get(entityId);
	if (ent->Removed()) return;
	ent->Remove();
	m_EntitiesToRemove.push(entityId);
}

void EntitySystem::addInteractable(InteractableEntity* entity) {
	m_Interactables.push_back(entity);
}

void EntitySystem::removeInteractable(InteractableEntity* entity) {
	m_InteractablesToRemove.push(entity);
}

void EntitySystem::cleanupEntities() {
	while (m_EntitiesToRemove.size() != 0) {
		auto id = m_EntitiesToRemove.front(); m_EntitiesToRemove.pop();
		if (m_Entities[id] != nullptr) {
			m_Entities[id].reset();
			m_UnusedEntityIds.push(id);
		}
	}

	while (m_InteractablesToRemove.size() != 0) {
		auto entity = m_InteractablesToRemove.front(); m_InteractablesToRemove.pop();
		m_Interactables.erase(std::remove(m_Interactables.begin(), m_Interactables.end(), entity), m_Interactables.end());
	}
}

EntityId EntitySystem::getNextId() {
	EntityId id = !m_UnusedEntityIds.empty() ? m_UnusedEntityIds.front() : m_Next++;
	if (!m_UnusedEntityIds.empty())m_UnusedEntityIds.pop();

	if (id + 1 > m_Entities.size()) m_Entities.resize(id + 1);
	return id;
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_SpriteBatcher == nullptr) {
		for (const auto& it : m_Entities)
			if (it != nullptr && !it->Deactivated())
				target.draw(*it, states);
	}
	else {
		for (const auto& it : m_Entities) {
			if (it == nullptr || it->Deactivated()) continue;
			m_SpriteBatcher->QueueObject(it.get());
		}
	}
}

void EntitySystem::drawGUI(sf::RenderWindow &window) {

	for (const auto& it : m_Entities) {
		if (it != nullptr && !it->Deactivated())
			it.get()->drawGUI(window, sf::RenderStates());
	}
}
