#include "EntityWall.h"


EntityWall::EntityWall(EntitySystem* system) : Entity(system)
{
}

EntityWall::~EntityWall() = default;

void EntityWall::Update()
{
	SetPosition(GetPosition() + sf::Vector3f(.5f, 0.f, .5f));
}
