#include "Building.h"
#include "..\Game.h"
#include "..\EntitySystem\EntitySystem.h"

Building::Building(EntitySystem* system, const EntityId& id) : TileEntity(system, id) 
{
	
}


Building::~Building()
{
	for (SubBuilding *b : subBuildings) {
		
		tileSystem->setTileEntity(b->tileX, b->tileY, b->tileZ, nullptr);
	    
		
		Game::instance().getEntitySystem().RemoveEntity(b);
		
		b = nullptr;
	}
	
}

sf::Vector3i Building::getCenter() {
	return sf::Vector3i();
}

//takes in relative position (tile coords) and sub building ptr
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
	
	if (CanPlaceHere(x,y,z)) {
				tileX = x;
				tileY = y;
				tileZ = z;
				for (SubBuilding *sb : subBuildings) {
					sb->tileX = tileX + sb->relX;
					sb->tileY = tileY + sb->relY;
					sb->tileZ = tileZ + sb->relZ;
					tileSystem->setTileEntity(sb->tileX, sb->tileY,sb->tileZ, this);
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
		if (!tileSystem->isInBounds(x + sb->relX, y+ sb->relY, z+ sb->relX)
			|| tileSystem->getTileEntity(x + sb->relX, y+ sb->relY, z+ sb->relX) != nullptr 
			|| (!tileSystem->canWalkHere(x + sb->relX, y+ sb->relY, z+ sb->relX) && occupiesTile)) {
			
			canplacehere = false;
		}
	}
	return canplacehere;
}



void Building::Update()
{
	if (heat != 0) {
		//Game::instance().getTileSystem().pathfinder->addHeat(sf::Vector2i(tileX,tileZ), heat);
	}
	if (GetHealth() == 0) {
		
		tileSystem->pathfinder->recalculateMap();
		GetSystem()->RemoveEntity(this);
	}
	
}

void Building::Load() {
	SetHealth(100);
	heat = 10.0f;
	SubBuilding *b = Game::instance().getEntitySystem().Add<SubBuilding>();
	AddSubBuilding(0, 0, 0, b);

	b =  Game::instance().getEntitySystem().Add<SubBuilding>();
	AddSubBuilding(0, 1, 0, b);

	b =  Game::instance().getEntitySystem().Add<SubBuilding>();
	AddSubBuilding(0, 2, 0, b);

	Entity::Load();
}


SubBuilding::SubBuilding(EntitySystem * system, const EntityId & id) : Entity(system,id){
}


bool SubBuilding::BindToBuilding(Building * ptr) {
	return false;
}



void SubBuilding::Update() {
}
