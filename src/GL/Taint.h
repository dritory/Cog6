#pragma once
#include "..\GameObject.h"
#include <SFML/Graphics.hpp>
class Taint : public GameObject {
public:
	Taint();

	~Taint();

	void addTaint(sf::Vector3f pos, float value);

	float drainTaint(float weight);
	float drainTaint();

private:
	float *taint;

	int size;
	int gridPerTileLength = 2;

	int width, height;
	
	int gridsize;

	sf::ConvexShape convex;
	sf::Texture texture;
	sf::Image overlay;
	sf::VertexArray varray;
	sf::Vector2i isoToGrid(sf::Vector3f pos);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
};

