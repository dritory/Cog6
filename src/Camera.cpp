#include "Camera.h"


Camera::Camera(sf::FloatRect bounds)
{
	this->view.reset(bounds);
	this->view.setCenter(bounds.left,bounds.top);
}

Camera::~Camera()
{
}

void Camera::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		view.zoom(0.90f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		view.zoom(1.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-1 * speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(1 * speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0,-1 * speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0,1 * speed);
	}
}

sf::View & Camera::getView() {
	return view;
}
