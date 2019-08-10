#include "PausedGui.h"

#include "../AssetLoader/AssetLoader.h"
PausedGui::PausedGui()
{
}

PausedGui::~PausedGui()
{
}

void PausedGui::initialize()
{
	sf::Font& font = *AssetLoader<sf::Font>::GetInstance().Get("C:/Windows/Fonts/SegoeUI.ttf");

	text.setFont(font);
	text.setPosition(400, 300);

}

void PausedGui::update(sf::Event & e, sf::RenderWindow & window)
{
}

void PausedGui::draw(sf::RenderTarget & target)
{
	text.setString("Paused");
	target.draw(text);
}
