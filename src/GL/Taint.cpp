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


	varray.setPrimitiveType(sf::Quads);
	varray.resize(4);
	varray[0].position = (Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f((width*tilesize / gridPerTileLength) + tilesize / 2, 0, (width*tilesize / gridPerTileLength) - tilesize / 2)));
	varray[1].position = Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(tilesize / 2, 0, height*tilesize / gridPerTileLength - tilesize / 2));
	varray[2].position = Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(tilesize / 2, 0, -tilesize / 2));
	varray[3].position = Game::Instance()->tileSystem->isoToWorldCoord(sf::Vector3f(width*tilesize / gridPerTileLength + tilesize / 2, 0, -tilesize / 2));

	
	varray[2].texCoords = sf::Vector2f(0, 0);
	varray[3].texCoords = sf::Vector2f(width, 0);
	varray[0].texCoords = sf::Vector2f(width, height);
	varray[1].texCoords = sf::Vector2f(0, height);

	texture.setSmooth(true);

	
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
		texture.update(overlay);
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

	state.texture = &texture;

	state.blendMode = sf::BlendAdd;

	target.draw(varray, state);
}
