#include "Player.h"
#include "..\Game.h"

#include "..\TileSystem\Tower.h"
#include "..\TileSystem\TileEntity.h"
#include "..\TileSystem\Base.h"

#include "..\TileSystem\Generator.h"
#include "..\EntitySystem\Entities\EntityMob.h"



Player::Player() {
}


Player::~Player() {
}

bool Player::build(int x, int y, int z, Building *building) {
	if (Game::instance().getTileSystem().isInBounds(x, y, z)) {


		if (transmutanium < building->getCost() || !building->BindToTile(x, y, z) && building != nullptr) {

			return false;
		}
		else {

			transmutanium -= building->getCost();
			int power = building->getPowerUsage();
			if (power < 0) {
				producedPower -= power;
			}
			else if (power > 0) {
				consumedPower += power;
			}
			buildings.push_back(building);

			return true;
		}
	}
	return false;
}

//really crappy code here 
//TODO: rewrite the whole class
void Player::Update(sf::Time elapsed) {
	static bool oldKeyState = false;

	//TODO: need a better way to represent ghostbuidlings
	static Building *building = Game::instance().getEntitySystem().Add<Building>();

	static Tower *tower = Game::instance().getEntitySystem().Add<Tower>();
	Game::instance().getEntitySystem().DeactivateEntity(tower);
	static Base *ex = Game::instance().getEntitySystem().Add<Base>();

	static Generator *gen = Game::instance().getEntitySystem().Add<Generator>();

	static Building *ghostBuilding = ex;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !oldKeyState) {
		if (state != BUILDING)
			state = BUILDING;
		else {
			state = IDLE;
			ghostBuilding->
		}

	}


	switch (state) {

	case BUILDING:
	{

		sf::Vector2i pos = Game::instance().getTileSystem().getMap(32).mouseToTile(Game::instance().getWindow());
		if (ghostBuilding)
			ghostBuilding->SetPosition(Game::instance().getTileSystem().tileToIsoCoord(sf::Vector3i(pos.x, 1, pos.y)));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//This needs a better way of doing
			Building *t;
			switch (typeBuilding) {

			case 3: {
				t = Game::instance().getEntitySystem().Add<Generator>();
				break;
			}
			case 2: {
				t = Game::instance().getEntitySystem().Add<Base>();
				break;
			}
			case 1: {
				t = Game::instance().getEntitySystem().Add<Tower>();
				break;
			}
			case 0:
			default:
			{
				t = Game::instance().getEntitySystem().Add<Building>();
				break;
			}
			}

			if (build(pos.x, 1, pos.y, t)) {

				Game::instance().getTileSystem().pathfinder->recalculateMap();

			}
			else {

				Game::instance().getEntitySystem().RemoveEntity(t);

			}
			break;
		}

		//Same goes for this snippet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			typeBuilding = 0;
			ghostBuilding->SetPosition(Game::instance().getTileSystem().tileToIsoCoord(sf::Vector3i(0, -10, 0)));
			ghostBuilding = building;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			typeBuilding = 1;
			ghostBuilding->SetPosition(Game::instance().getTileSystem().tileToIsoCoord(sf::Vector3i(0, -10, 0)));
			ghostBuilding = tower;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			typeBuilding = 2;
			ghostBuilding->SetPosition(Game::instance().getTileSystem().tileToIsoCoord(sf::Vector3i(0, -10, 0)));
			ghostBuilding = ex;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			typeBuilding = 3;
			ghostBuilding->SetPosition(Game::instance().getTileSystem().tileToIsoCoord(sf::Vector3i(0, -10, 0)));
			ghostBuilding = gen;
		}
		break;

	}
	case IDLE: {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			for ( int i = 0; i < 1; i++ ) {
				sf::Vector2f cam = Game::instance().getTileSystem().getMap(32).screenToIso(sf::Mouse::getPosition(Game::instance().getWindow()), Game::instance().getWindow());
				Game::instance().getSpawner().spawn<EntityMob>(cam.x, 32.0f, cam.y);
			}
		}
		break;

	}


	}

	oldKeyState = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
}

int Player::getPowerEfficienty() {
	int diff = producedPower - consumedPower;
	if (producedPower == 0) {
		return 0;
	}
	if ( diff >= 0) {
		return 100;
	}
	int p = (100*producedPower) + producedPower * (diff) ;
	if (p > 0)
		return p / 100;
	else
		return 0;
	
}

void Player::removeBuilding(Building * building) {


	std::vector<Building *>::iterator it;
	for (it = buildings.begin(); it != buildings.end(); it++) {
		if (*it == building) {
			int power = building->getPowerUsage();
			if (power > 0)
				consumedPower -= power;
			else
				producedPower += power;

			buildings.erase(it);

			return;
		}
	}

}

void Player::load()
{

	typeBuilding = 2;
	state = BUILDING;
}
