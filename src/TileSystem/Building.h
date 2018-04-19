#pragma once
#include "TileEntity.h"
class Building : public TileEntity
{
public:
	Building(EntitySystem* system, const EntityId& id);
	~Building();


private:
protected:
	
	void Update() override;
	std::string GetSpriteLocation() override { return "wall.png"; }
};

