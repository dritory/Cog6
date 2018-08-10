#pragma once
#include "..\PlayState.h"

class Spawner {
public:
	Spawner();
	~Spawner();



	template <class entity>
	entity * AddToPool() {

		entity * ent = Game::Instance()->entitysystem->Add<entity>();
		mobpool.push_back(ent);
		return ent;
	}
	template <class entity>
	bool RemoveFromPool(entity * ent) {
		mobpool.erase(ent);
	}

	void update(sf::Time elapsed);

	std::vector<Entity *> & getUsedMobs() { return usedMobs; };


	template <class TYPE>
	//isocoords
	bool spawn(float x, float y, float z) {
		if ( Game::Instance()->tileSystem->pathfinder->isValidAt(x, z) ) {
			for ( auto p = unusedMobs.begin(); p != unusedMobs.end(); p++ ) {
				TYPE* type = dynamic_cast<TYPE*> (*p);
				if ( type != nullptr ) { //the mob is of the same type

					Game::Instance()->entitysystem->ActivateEntity(*p);
					(*p)->SetPosition(sf::Vector3f(x, y, z));
					(*p)->SetHealthToMax();
					usedMobs.push_back(*p);
					p = unusedMobs.erase(p);

					return true;
				}
			}

			TYPE* entity = AddToPool<TYPE>();
			entity->SetPosition(sf::Vector3f(x, y, z));
			entity->SetHealthToMax();
			usedMobs.push_back(entity);
			return true;
		}
		return false;
	}


	void load();

private:

	sf::Clock spawnerClock;
	sf::Clock waveClock;

	int waveInterval = 2;//in seconds
	int waveDuration = 5;//in seconds
	int spawnInterval = 100; //in milliseconds

	int entityLimit = 2000;

	

	std::vector<Entity *> unusedMobs;
	std::vector<Entity *> usedMobs;

	std::vector<Entity *> mobpool;
};

