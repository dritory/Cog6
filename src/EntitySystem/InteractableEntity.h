#pragma once
#include "EntitySystem.h"

class Entity;

class InteractableEntity
{
public:
	InteractableEntity(EntitySystem* system, Entity* entity)
	{
		m_System = system;
		m_Entity = entity;
		m_System->addInteractable(this);
	}

	virtual ~InteractableEntity()
	{
		m_System->removeInteractable(this);
	}

	virtual bool CanInteract(Entity* other) { return true; }

protected:
	virtual void Interact(Entity* other) = 0;

private:
	friend class EntitySystem;

	EntitySystem* m_System;
	Entity* m_Entity;
};
