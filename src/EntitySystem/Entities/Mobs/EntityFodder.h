#pragma once
#include "../../Entity.h"
#include "EntityMob.h"
class EntityFodder : public EntityMob {
public:
	EntityFodder(EntitySystem* system, const EntityId& id);
	~EntityFodder();
	static int getSpawnNumber(int round, int diff);

protected:
	void Update() override;

	virtual void FixedUpdate(sf::Time elapsed) override;

	std::string GetSpriteLocation() override { return "sheet2.png"; }
};

