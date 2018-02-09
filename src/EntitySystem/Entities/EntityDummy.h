#pragma once

#include "../Entity.h"

class EntityDummy : public Entity
{
public:
	EntityDummy(EntitySystem* system, const EntityId& id);
	~EntityDummy();
protected:
	void Update() override;
	std::string GetSpriteLocation() override { return "grass.png"; }
};