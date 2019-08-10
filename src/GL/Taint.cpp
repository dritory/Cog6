#include "Taint.h"
#include "..\PlayState.h"
Taint::Taint()
{
	height = Game::Instance()->tileSystem->getWidth()*gridPerTileLength;
	width = height;
	this->size = width * height;
	taint = new float[size];
	int tilesize = Game::Instance()->tileSystem->getTileSize();
	gridsize = tilesize / gridPerTileLength;
	
	for ( int i = 0; i < width*height; i++ ) {
		taint[i] = 0;
	}
	texture.create(width, height);
	overlay.create(width, height, sf::Color::Transparent);
	texture.loadFromImage(overlay);

	convex.setPointCount(4);
	convex.setPoint(2, Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(tilesize/2, 0, -tilesize/2)));
	convex.setPoint(3, Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(width*tilesize /gridPerTileLength + tilesize/2,0, -tilesize/2)));
	convex.setPoint(0, Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f((width*tilesize / gridPerTileLength) + tilesize / 2, 0, (width*tilesize / gridPerTileLength) - tilesize/2)));
	convex.setPoint(1, Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(tilesize / 2, 0, height*tilesize / gridPerTileLength - tilesize / 2) ));

	convex.setTexture(&texture);
	
	SetPosition(sf::Vector3f(width*tilesize / gridPerTileLength, 0, width*tilesize / gridPerTileLength));
}

Taint::~Taint()
{
	delete[] taint;
	taint = nullptr;
}

void Taint::addTaint(sf::Vector3f pos, float value)
{
	sf::Vector2i grid = isoToGrid(pos);
	if ( grid.x >= 0 && grid.x < width && grid.y >= 0 && grid.y < height ) {
		taint[grid.x*grid.y] += value;
		int8_t r = 200;
		int8_t g = 50;
		int8_t b = 200;
		int8_t a = (int8_t)taint[grid.x*grid.y];
		if ( taint[grid.x*grid.y] > 255 ) {
			a = 255;
		}

		overlay.setPixel(grid.x, grid.y, sf::Color(r, g, b, a));
	}
}

float Taint::drainTaint(float weight)
{
	float v;
	for ( int i = 0; i < size; i++ ) {
		
		if ( taint[i] > weight ) {
			taint[i] -= weight;
			v += weight;
			int8_t r = 200;
			int8_t g = 50;
			int8_t b = 200;
			int8_t a = (int8_t) taint[i];
			if ( taint[i] > 255 ) {
				a = 255;
			}

			overlay.setPixel(i % width, i / width, sf::Color(r, g, b, a));

		}
		else {
			v += taint[i];
			taint[i] = 0;
			overlay.setPixel(i % width, i / width, sf::Color::Transparent);
		}
	}
	return v;
}

float Taint::drainTaint()
{
	return drainTaint(FLT_MAX);
}

sf::Vector2i Taint::isoToGrid(sf::Vector3f pos)
{
	return sf::Vector2i(pos.x / gridsize, pos.z / gridsize);
}

void Taint::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	//sf::RenderStates newState(sf::BlendAlpha);
	target.draw(convex, state);
}
