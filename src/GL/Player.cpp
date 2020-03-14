#include "Player.h"
#include "..\PlayState.h"

#include "..\TileSystem\Tower.h"
#include "..\TileSystem\TileEntity.h"
#include "..\TileSystem\Base.h"

#include "..\TileSystem\Generator.h"
#include "..\EntitySystem\Entities/Mobs\EntityMob.h"



Player::Player() {
}


Player::~Player() {
}

bool Player::build(int x, int y, int z, Building *building) {
	if (Game::Instance()->tileSystem->isInBounds(x, y, z) && building) {


		if (transmutanium < building->getCost() || !building->BindToTile(x, y, z)) {

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
			Game::Instance()->entitysystem->ActivateEntity(building);
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



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !oldKeyState) {

		Game::Instance()->ToggleFreeze();

	}


	switch (state) {

	case BUILDING:
	{

		sf::Vector2i pos = Game::Instance()->tileSystem->getMap(32).mouseToTile(Game::Instance()->getWindow());
		if (ghostBuilding)
			ghostBuilding->SetPosition(Game::Instance()->tileSystem->tileToIsoCoord(sf::Vector3i(pos.x + 32, 33, pos.y + 32)));
		else {
			ghostBuilding = chooseBuilding(typeBuilding, nullptr);
		}
		ghostBuilding->CanPlaceHere(pos.x, 1, pos.y, true);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Game::Instance()->gui->isMouseOverGUI()) {

			if (build(pos.x, 1, pos.y, ghostBuilding)) {
				sf::Time timeSinceLast = buildTimer.restart();
				if (timeSinceLast.asMilliseconds() >= 500) {
					Game::Instance()->tileSystem->pathfinder->recalculateMap();
				}
				ghostBuilding = chooseBuilding(typeBuilding);
			}
			else {

			}
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			ghostBuilding = chooseBuilding(0, ghostBuilding);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			ghostBuilding = chooseBuilding(1, ghostBuilding);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			ghostBuilding = chooseBuilding(2, ghostBuilding);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			ghostBuilding = chooseBuilding(3, ghostBuilding);
		}
		break;

	}
	case IDLE: {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			for (int i = 0; i < 1; i++) {
				sf::Vector2f cam = Game::Instance()->tileSystem->getMap(32).screenToIso(sf::Mouse::getPosition(Game::Instance()->getWindow()), Game::Instance()->getWindow());
				Game::Instance()->spawner->forceSpawn<EntityFodder>(Game::Instance()->spawner->fodder, cam.x, 32.0f, cam.y);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			sf::Vector2f cam = Game::Instance()->tileSystem->getMap(32).screenToIso(sf::Mouse::getPosition(Game::Instance()->getWindow()), Game::Instance()->getWindow());
			Game::Instance()->tileSystem->pathfinder->addTarget(cam.x / 32, cam.y / 32);
			Game::Instance()->tileSystem->pathfinder->recalculateMap();
		}
		break;

	}


	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
		Game::Instance()->Unload();
		Game::Instance()->Init();
	}

	oldKeyState = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

int Player::getPowerEfficienty() {
	int diff = producedPower - consumedPower;
	if (producedPower == 0) {
		return 0;
	}
	if (diff >= 0) {
		return 100;
	}
	int p = (100 * producedPower) + producedPower * (diff);
	if (p > 0)
		return p / 100;
	else
		return 0;

}

void Player::addTM(int tm) {

	transmutanium += tm;
	Game::Instance()->bus->notify(Event::Transmutanium{ tm });

}

void Player::toggleBuildState() {
	if (state != BUILDING) {
		state = BUILDING;
		if (ghostBuilding)
			ghostBuilding->setHidden(false);
	}
	else {
		state = IDLE;
		if (ghostBuilding)
			ghostBuilding->setHidden(true);
	}
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

void Player::load() {
	typeBuilding = 2;
	state = IDLE;
	ghostBuilding = chooseBuilding(typeBuilding);
}

Building* Player::chooseBuilding(int type, Building * ghost) {
	typeBuilding = type;
	Building *ptr = nullptr;
	switch (type) {
	case 3: {
		ptr = changeBuilding<Generator>(ghost);
		break;
	}
	case 2: {
		ptr = changeBuilding<Base>(ghost);
		break;
	}
	case 1: {
		ptr = changeBuilding<Tower>(ghost);
		break;
	}
	case 0:
	default:
	{
		ptr = changeBuilding<Building>(ghost);
		break;
	}
	}
	return ptr;
}
