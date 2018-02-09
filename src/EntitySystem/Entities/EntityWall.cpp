#include "EntityWall.h"


EntityWall::EntityWall(EntitySystem* system, const EntityId& id) : Entity(system, id), InteractableEntity(system, this)
{
}

EntityWall::~EntityWall() = default;

void EntityWall::Update()
{
}

void EntityWall::Interact(Entity* other)
{
	if (rand() > 1) return;
	GetSystem()->RemoveEntity(GetId());
}
