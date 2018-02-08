#pragma once

#include "../Entity.h"

class EntityWall : public Entity
{
public:
	EntityWall(EntitySystem* system);
	~EntityWall();
protected:
	void Update() override;
	std::string GetSpriteLocation() override { return "test.png"; }
};