#pragma once
#include <SFML\Graphics.hpp>
class Camera
{
public:
	Camera(sf::FloatRect bounds);
	~Camera();

	void update(sf::Time elapsed);

	sf::View& getView();

	sf::View view;
private:
	float speed = 1.5f;
};

