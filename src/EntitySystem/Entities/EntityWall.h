#pragma once

#include "../Entity.h"
#include "../InteractableEntity.h"

class EntityWall : public Entity, public InteractableEntity
{
public:
	EntityWall(EntitySystem* system, const EntityId& id);
	~EntityWall();
protected:
	void Update() override;
	std::string GetSpriteLocation() override { return "test.png"; }
	void Interact(Entity* other) override;
};