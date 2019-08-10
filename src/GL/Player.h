#pragma once
#include "..\PlayState.h"
#include "..\TileSystem\Building.h"
enum PlayerState {
	IDLE,
	BUILDING
};
class Building;
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
	
	void setState(PlayerState state) {
		this->state = state;
	}
	
	void toggleBuildState();

	void removeBuilding(Building *building);

	void load();

private:

	sf::Clock buildTimer;
	int typeBuilding;


	int producedPower;
	int consumedPower;

	int transmutanium = 100;

	Building *ghostBuilding = nullptr;

	PlayerState state;

	std::vector<Building *> buildings;

	template<class TYPE>
	TYPE *changeBuilding(Building *old = nullptr) {
		if(old !=nullptr)
			Game::Instance()->entitysystem->RemoveEntity(old);
		TYPE * next = Game::Instance()->entitysystem->Add<TYPE>();
		Game::Instance()->entitysystem->DeactivateEntity(next);
		return next;
	};
	
	Building *chooseBuilding(int type, Building *ghost = nullptr);

};

