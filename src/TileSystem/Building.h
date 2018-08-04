#pragma once
#include "TileEntity.h"
#include <vector>
#include <memory>

class SubBuilding;

class Building : public TileEntity {
public:
	Building(EntitySystem* system, const EntityId& id);
	~Building();

	sf::Vector3i getCenter();
	void AddSubBuilding(int relx, int rely, int relz, SubBuilding * building);
	void AddSubBuilding(int relx, int rely, int relz, std::string building);
	void AddSubBuilding(int relx, int rely, int relz);
	virtual bool BindToTile(int tilex, int tiley, int tilez);


	bool CanPlaceHere(int x, int y, int z);

	bool isValid() { return (tileX >= 0 && tileY >= 0 && tileZ >= 0); }

	int getCost() { return cost; };
	int getPowerUsage() { return powerUsage; }
	int getMaxHealth() { return maxHealth; }

	//overriden in order to move subbuildings
	virtual void SetPosition(const sf::Vector3f& position) override;

protected:

	std::vector<SubBuilding *> subBuildings;

	int cost = 10;
	int powerUsage = 0;


	virtual void Load() override;
	virtual void Update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::string GetSpriteLocation() override { return ""; }

private:


};

class SubBuilding : public Entity {
public:
	SubBuilding(EntitySystem* system, const EntityId& id);
	~SubBuilding() = default;


	virtual bool BindToBuilding(Building *ptr);

	

	sf::Vector3f getRelPos();
	sf::Vector3i getRelTilePos();

private:


	int tileX, tileY, tileZ;
	int relX, relY, relZ;
	friend Building;
protected:

	
	virtual void Update();
	std::string GetSpriteLocation() override { return "wall.png"; };
};
