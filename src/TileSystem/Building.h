#pragma once
#include "TileEntity.h"
#include <vector>

class SubBuilding;

class Building : public TileEntity {
public:
	Building(EntitySystem* system, const EntityId& id);
	~Building();

	sf::Vector3i getCenter();
	void AddSubBuilding(int tilex, int tiley, int tilez, SubBuilding * building);
	bool BindToTile(int tilex, int tiley, int tilez) override;

	bool CanPlaceHere(int x, int y, int z);
private:

	std::vector<SubBuilding *> subBuildings;

	

protected:

	void Load() override;
	void Update() override;
	std::string GetSpriteLocation() override { return ""; }
};

class SubBuilding : public Entity {
public:
	SubBuilding(EntitySystem* system, const EntityId& id);
	~SubBuilding() = default;


	bool BindToBuilding(Building *ptr);

private:

	int tileX, tileY, tileZ;
	int relX, relY, relZ;
	friend Building;
protected:

	void Update() override;
	std::string GetSpriteLocation() override { return "wall.png"; };
};
