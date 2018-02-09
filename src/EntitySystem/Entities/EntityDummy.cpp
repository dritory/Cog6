#include "EntityDummy.h"

EntityDummy::EntityDummy(EntitySystem* system, const EntityId& id) : Entity(system, id)
{
}

EntityDummy::~EntityDummy() = default;

void EntityDummy::Update()
{
}
