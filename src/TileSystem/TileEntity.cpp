#include "TileEntity.h"
#include "..\PlayState.h"

TileEntity::TileEntity(EntitySystem* system, const EntityId& id) : Entity(system, id) {
	Game::Instance()->tileSystem = Game::Instance()->tileSystem;
	tileX = -1;
	tileY = -1;
	tileZ = -1;
}

TileEntity::~TileEntity()
{
	if (collidable) {
		Game::Instance()->tileSystem->setCollision(tileX, tileY, tileZ, isTileCollidable);
	}
	Game::Instance()->tileSystem->setTileEntity(tileX, tileY, tileZ, nullptr);
}
void TileEntity::damage(int d) {
	SetHealth((GetHealth() - d > 0 ? GetHealth() - d : 0));
}
 bool TileEntity::BindToTile(int x, int y, int z)
{
	if ( Game::Instance()->tileSystem->isInBounds(x, y, z) && Game::Instance()->tileSystem->getTileEntity(x,y,z) == nullptr) {
		if (occupiesTile == false || Game::Instance()->tileSystem->canWalkHere(x, y, z)) {
			tileX = x;
			tileY = y;
			tileZ = z;
			Game::Instance()->tileSystem->setTileEntity(x, y, z, this);
			SetPosition(Game::Instance()->tileSystem->tileToIsoCoord(sf::Vector3i(x, y, z)));
			if (collidable) {
				isTileCollidable = Game::Instance()->tileSystem->canWalkHere(x, y, z);
				Game::Instance()->tileSystem->setCollision(x, y, z, collidable);
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



