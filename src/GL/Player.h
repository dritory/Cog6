#pragma once

#include "..\TileSystem\Building.h"
enum PlayerState {
	IDLE,
	BUILDING
};

class Player {
public:
	Player();
	~Player();

	//tile coords
	
	bool build(int x, int y, int z, Building *building);

	void Update(sf::Time elapsed);


	int getPowerEfficienty();
	

	int getTM() { return transmutanium; }

	void addTM(int tm) { transmutanium += tm; }

	PlayerState getState() { return state; }
	
	void removeBuilding(Building *building);


private:

	
	int typeBuilding = 0;


	int producedPower;
	int consumedPower;

	int transmutanium = 10000;

	PlayerState state;

	std::vector<Building *> buildings;

};

