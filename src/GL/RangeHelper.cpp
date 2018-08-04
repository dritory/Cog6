#include "RangeHelper.h"

RangeHelper::RangeHelper(int width, int length) : lenght(length), width(width)
{
	
}

void RangeHelper::addEntity(int x, int z, Entity * entity)
{
	if ( x >= 0 && x < width && z >= 0 && z < lenght ) {
		
		entities[index(x,z)].push_back(entity);
	}
}

void RangeHelper::flush()
{
	for ( auto a = entities.begin(); a != entities.end(); a++) {
		if ( a->second.size() > 0 ) {
			for ( auto b : a->second ) {
				b = nullptr;
			}
			a->second.clear();
		}
		else {
			//entities.erase(a->first);
		}
	}
	entities.clear();
}

void RangeHelper::Update(sf::Time elapsed)
{
	/*
	flush();
	int tsize = Game::instance().getTileSystem().getTileSize();
	int size = Game::instance().getSpawner().getUsedMobs().size();
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {
		sf::Vector3f pos = e->GetPosition();
		addEntity(pos.x / tsize, pos.z / tsize, e);
	}
	*/
}

std::vector<Entity*> RangeHelper::getEntities(int x, int z)
{
	if (z >= 0 && x >= 0 && z < lenght && x < width) {
		return entities[index(x,z)];
	}
	else
		return std::vector<Entity *>();
}
/*
std::vector<Entity*> RangeHelper::entitiesInRange(int x, int z, float range)
{
	int tsize = Game::instance().getTileSystem().getTileSize();
	std::vector<Entity *> temp;
	
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {
		
		sf::Vector3f pos = e->GetPosition();
		float dx = ((pos.x / tsize) - x);
		float dy = ((pos.z / tsize) - z);
		float distance = (dx*dx + dy*dy);
		if ( distance <= range * range ) {
			temp.push_back(e);
		}
	}
	
	/*

	if (ranges.find(range) == ranges.end()) {
		ranges[range] = getRangeArray(range);
	}
	for (const sf::Vector2i &pos : ranges.find(range)->second ) {
		Game::instance().getTileSystem().setColor(pos.x + x, 0, pos.y + z, sf::Color(255,200,255));
		int i = index(pos.x + x, pos.y + z);
		const auto &list = entities.find(i);
		if (list != entities.end() ) {
			for ( auto e : list->second ) {
				temp.push_back(e);
			}
		}
	}
	
	
	return temp;
}
/*
EntityMob * RangeHelper::getEntity(int x, int z, float range, Priority priority)
{
	switch ( priority ) {
	case CLOSEST:
		return getClosestEntity(x, z, range);
	case FURTHEST:
		return getFurthestEntity(x, z, range);
	case STRONGEST:
		return getStrongestEntity(x, z, range);
	case WEAKEST:
		return getWeakestEntity(x, z, range);
	default:
		int tsize = Game::instance().getTileSystem().getTileSize();
		for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {
			sf::Vector3f pos = e->GetPosition();
			float dx = ((pos.x / tsize) - x);
			float dy = ((pos.z / tsize) - z);
			float distance = (dx*dx + dy * dy);
			if ( distance <= range * range ) {
				return e;

			}
		}

	}
	return nullptr;
}

EntityMob * RangeHelper::getClosestEntity(int x, int z, float range)
{
	std::vector<EntityMob *> inrange = entitiesInRange(x, z, range);
	EntityMob * entity = nullptr;
	int dist = range * range;
	int tsize = Game::instance().getTileSystem().getTileSize();
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {

		sf::Vector3f pos = e->GetPosition();
		float dx = ((pos.x / tsize) - x);
		float dy = ((pos.z / tsize) - z);
		float distance = (dx*dx + dy * dy);
		if ( distance <= range * range ) {
			
			if ( distance < dist ) {
				entity = e;
				dist = distance;
			}

		}
	}
	return entity;
}

EntityMob * RangeHelper::getFurthestEntity(int x, int z, float range)
{
	std::vector<EntityMob *> inrange = entitiesInRange(x, z, range);
	EntityMob * entity = nullptr;
	int dist = 0;
	int tsize = Game::instance().getTileSystem().getTileSize();
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {

		sf::Vector3f pos = e->GetPosition();
		float dx = ((pos.x / tsize) - x);
		float dy = ((pos.z / tsize) - z);
		float distance = (dx*dx + dy * dy);
		if ( distance <= range * range ) {

			if ( distance > dist ) {
				entity = e;
				dist = distance;
			}

		}
	}
	return entity;
}

EntityMob * RangeHelper::getStrongestEntity(int x, int z, float range)
{
	std::vector<EntityMob *> inrange = entitiesInRange(x, z, range);
	EntityMob * entity = nullptr;
	int health = 0;
	int tsize = Game::instance().getTileSystem().getTileSize();
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {

		sf::Vector3f pos = e->GetPosition();
		float dx = ((pos.x / tsize) - x);
		float dy = ((pos.z / tsize) - z);
		float distance = (dx*dx + dy * dy);
		if ( distance <= range * range ) {
			int h = e->GetHealth();
			if (h > health ) {
				entity = e;
				health = h;
			}

		}
	}
	return entity;
}

EntityMob * RangeHelper::getWeakestEntity(int x, int z, float range)
{
	std::vector<EntityMob *> inrange = entitiesInRange(x, z, range);
	EntityMob * entity = nullptr;
	int health = INT_MAX;
	int tsize = Game::instance().getTileSystem().getTileSize();
	for ( auto e : Game::instance().getSpawner().getUsedMobs() ) {

		sf::Vector3f pos = e->GetPosition();
		float dx = ((pos.x / tsize) - x);
		float dy = ((pos.z / tsize) - z);
		float distance = (dx*dx + dy * dy);
		if ( distance <= range * range ) {
			int h = e->GetHealth();
			if ( h < health ) {
				entity = e;
				health = h;
			}

		}
	}
	return entity;
}
*/
std::vector<sf::Vector2i> RangeHelper::getRangeArray(float range)
{

	std::vector<sf::Vector2i> tempArray;

	for (int i = -range; i <= range; i++) {
		for (int j = -range; j <= range; j++) {
			
			if (i*i + j * j <= range * range) {
				tempArray.push_back(sf::Vector2i(i,j));
			}

		}
	}


	return tempArray;
}
