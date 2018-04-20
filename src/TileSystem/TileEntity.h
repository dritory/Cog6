#pragma once

#include "../EntitySystem/Entity.h"
#include "../EntitySystem/InteractableEntity.h"
#include "TileSystem.h"
class TileSystem;
class TileEntity : public Entity {
public:
	TileEntity(EntitySystem* system, const EntityId& id);
	~TileEntity();

	bool BindToTile(int x, int y, int z);

	sf::Vector3i getTilePos();
	
	void damage(int d);

	float getHeat() {
		return heat;
	};
private:

protected:
	TileSystem *tileSystem;
	
	float heat = 100.0f;
	bool occupiesTile = true;
	bool collidable = false;
	bool isTileCollidable = false;
	int tileX, tileY, tileZ;
};
