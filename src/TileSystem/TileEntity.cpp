#include "TileEntity.h"
#include "..\Game.h"


TileEntity::TileEntity(EntitySystem* system, const EntityId& id) : Entity(system, id) {
	this->tileSystem = &Game::instance().getTileSystem();
	tileX = -1;
	tileY = -1;
	tileZ = -1;
}

TileEntity::~TileEntity()
{
	if (collidable) {
		tileSystem->setCollision(tileX, tileY, tileZ, isTileCollidable);
	}
	tileSystem->setTileEntity(tileX, tileY, tileZ, nullptr);
	this->tileSystem = nullptr;
}
void TileEntity::damage(int d) {
	SetHealth((GetHealth() - d > 0 ? GetHealth() - d : 0));
}
 bool TileEntity::BindToTile(int x, int y, int z)
{
	if (tileSystem->isInBounds(x, y, z) && tileSystem->getTileEntity(x,y,z) == nullptr) {
		if (occupiesTile == false || tileSystem->canWalkHere(x, y, z)) {
			tileX = x;
			tileY = y;
			tileZ = z;
			tileSystem->setTileEntity(x, y, z, this);
			SetPosition(tileSystem->tileToIsoCoord(sf::Vector3i(x, y, z)));
			if (collidable) {
				isTileCollidable = tileSystem->canWalkHere(x, y, z);
				tileSystem->setCollision(x, y, z, collidable);
			}
			return true;
		}
	}
	return false;
}

sf::Vector3i TileEntity::getTilePos()
{
	return sf::Vector3i(tileX,tileY,tileZ);
}

