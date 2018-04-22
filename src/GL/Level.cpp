#include "Level.h"



Level::Level() {
	this->game = &Game::instance();
}



Level::~Level() {

	this->game = nullptr;
}
