#include "Building.h"
#include "..\Game.h"
#include "..\EntitySystem\EntitySystem.h"

Building::Building(EntitySystem* system, const EntityId& id) : TileEntity(system, id) {

}


Building::~Building() {
	for (SubBuilding *b : subBuildings) {

		tileSystem->setTileEntity(b->tileX, b->tileY, b->tileZ, nullptr);


		Game::instance().getEntitySystem().RemoveEntity(b);

		b = nullptr;
	}
	Game::instance().getPlayer().removeBuilding(this);
}

sf::Vector3i Building::getCenter() {
	return sf::Vector3i();
}

//takes in relative position (tile coords) and sub building ptr
void Building::AddSubBuilding(int relx, int rely, int relz, std::string texture) {
	SubBuilding *building = Game::instance().getEntitySystem().Add<SubBuilding>("",texture);
	AddSubBuilding(relx, rely, relz, building);

}
void Building::AddSubBuilding(int relx, int rely, int relz)
{
	SubBuilding *building = Game::instance().getEntitySystem().Add<SubBuilding>();
	AddSubBuilding(relx, rely, relz, building);
}
void Building::AddSubBuilding(int relx, int rely, int relz, SubBuilding * building) {

	building->relX = relx;
	building->relY = rely;
	building->relZ = relz;

	building->tileX = tileX + relx;
	building->tileY = tileY + rely;
	building->tileZ = tileZ + relz;

	subBuildings.push_back(building);

}




bool Building::BindToTile(int x, int y, int z) {

	if (CanPlaceHere(x, y, z)) {
		tileX = x;
		tileY = y;
		tileZ = z;
		for (SubBuilding *sb : subBuildings) {
			sb->tileX = tileX + sb->relX;
			sb->tileY = tileY + sb->relY;
			sb->tileZ = tileZ + sb->relZ;
			tileSystem->setTileEntity(sb->tileX, sb->tileY, sb->tileZ, this);
			sb->SetPosition(tileSystem->tileToIsoCoord(sf::Vector3i(sb->tileX, sb->tileY, sb->tileZ)));

		}
		SetPosition(tileSystem->tileToIsoCoord(sf::Vector3i(x, y, z)));


		/*
		if (collidable) {
			isTileCollidable = tileSystem->canWalkHere(x, y, z);
			tileSystem->setCollision(x, y, z, collidable);
			}
		*/
		return true;
	}
	return false;
}



bool Building::CanPlaceHere(int x, int y, int z) {   
	bool canplacehere = true;
	for (SubBuilding *sb : subBuildings) {
		if (!tileSystem->isInBounds(x + sb->relX, y + sb->relY, z + sb->relZ) || tileSystem->getTileEntity(x + sb->relX, y + sb->relY, z + sb->relZ) != nullptr || (!tileSystem->canWalkHere(x + sb->relX, y + sb->relY, z + sb->relZ))) {

			canplacehere = false;
		}
	}
	return canplacehere;
}



void Building::Update() {
	if (!isAlive()) {
		Game::instance().getEntitySystem().RemoveEntity(this);
	}
	Entity::Update();
}

void Building::Load() {
	SetHealth(500);
	maxHealth = 500;
	heat = 0.01f;
	AddSubBuilding(0, 0, 0);
	
	Entity::Load();
}


void Building::SetPosition(const sf::Vector3f & position) {

	for (auto s : subBuildings) {
		s->SetPosition(position + s->getRelPos());
	}
	
	
	Entity::SetPosition(position);
}


void Building::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);

}





SubBuilding::SubBuilding(EntitySystem * system, const EntityId & id) : Entity(system,id){
}


bool SubBuilding::BindToBuilding(Building * ptr) {
	return false;
}

sf::Vector3f SubBuilding::getRelPos() {
	float size = Game::instance().getTileSystem().getTileSize();
	return sf::Vector3f(size*relX,size*relY,size*relZ);
}

sf::Vector3i SubBuilding::getRelTilePos() {
	return sf::Vector3i(relX,relY,relZ);
}



void SubBuilding::Update() {
}
