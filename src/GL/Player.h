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

	void load();

private:

	
	int typeBuilding;


	int producedPower;
	int consumedPower;

	int transmutanium = 100;

	PlayerState state;

	std::vector<Building *> buildings;

	template<class TYPE>
	TYPE *createGhostBuilding() {
		TYPE * ghost = Game::instance().getEntitySystem().Add<TYPE>();
		Game::instance().getEntitySystem().DeactivateEntity(ghost);
	};
	

};

