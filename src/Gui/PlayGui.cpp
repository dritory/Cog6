#include "PlayGui.h"
#include "../AssetLoader/AssetLoader.h"
#include "../PlayState.h"
#include "../GL/Spawner.h"
#include "../PlayState.h"
#include "../EntitySystem/Entities/Particle.h"
PlayGui::PlayGui()
{

}

PlayGui::~PlayGui()
{
	for ( auto o : objects ) {
		delete o;
	}
}

void PlayGui::initialize()
{
	bool loaded = AssetLoader<sf::Font>::GetInstance().LoadAsset("C:/Windows/Fonts/SegoeUI.ttf");
	if ( !loaded ) {
		std::cout << "Could not load font" << std::endl;
		return;
	}
	sf::Font& font = *AssetLoader<sf::Font>::GetInstance().Get("C:/Windows/Fonts/SegoeUI.ttf");
	
	

	text1.setFont(font);
	text1.setPosition(800, 80);

	text2.setFont(font);
	text2.setPosition(800, 110);



	text = new Text("TrMut:", font, sf::Vector2f(800, 50));
	objects.push_back(text);

	text4 = new Text("FPS:", font, sf::Vector2f(50, 50));
	objects.push_back(text4);

	text5 = new Text("FFPS:", font, sf::Vector2f(50, 80));
	objects.push_back(text5);

	text6 = new Text("Entities:", font, sf::Vector2f(50, 110));
	objects.push_back(text6);

	addButton("Next Wave", sf::Vector2f(1050, 750), [this] () {

		Game::Instance()->spawner->startNextWave();

	});

	buildButton = new Button("Build", font,sf::Vector2f(1050, 700));
	
	buildButton->setCallback([this] () {

		Game::Instance()->player->toggleBuildState();
		buildButton->setHidden(true);
		exitBuildButton->setHidden(false); 
	});
	exitBuildButton = new Button("Exit", font, sf::Vector2f(1050, 700));
	exitBuildButton->setHidden(true);
	exitBuildButton->setCallback([this] () {

		Game::Instance()->player->toggleBuildState();
		buildButton->setHidden(false);
		exitBuildButton->setHidden(true);
	});

	addButton("Test",sf::Vector2f(1050,500), [this] () {
		Particle *p = Game::Instance()->entitysystem->Add<Particle>();
		p->SetPosition(sf::Vector3f(32, 128,32 ));
		p->SetVelocity(sf::Vector3f(rand() % 500, rand() % 2000, rand() % 500));
		p->SetHealthToMax();
		p->ToggleCollision(true);
		p->ToggleGravity(true);
		Game::Instance()->entitysystem->ActivateEntity(p);
	});


	addButton(buildButton);
	addButton(exitBuildButton);
	//addButton("test", sf::Vector2f(100, 100), NULL);
}


void PlayGui::update(sf::Event & e, sf::RenderWindow & window) {
	for ( auto o : objects ) {
		if (!o->isHidden()) 
			o->update(e, window);
	}

}


void PlayGui::draw(sf::RenderTarget& target)
{

	text->setString("TrMut: " + std::to_string(Game::Instance()->player->getTM()));
	text4->setString("FPS: " + std::to_string(Game::Instance()->getFPS()));
	text5->setString("FFPS: " + std::to_string(Game::Instance()->getFFPS()));
	text6->setString("Entities: " + std::to_string(Game::Instance()->entitysystem->GetCount()));
	text1.setString("Power: " + std::to_string(Game::Instance()->player->getPowerEfficienty()) + "%");
	text2.setString("Wave: " + std::to_string(Game::Instance()->spawner->getWave()));

	target.draw(text1);
	target.draw(text2);

	for ( auto o : objects ) {
		if(!o->isHidden())
			target.draw(*o);
	}

}

void PlayGui::addButton(const sf::String &s, const sf::Vector2f & pos, Button::Callback callback)
{
	Button* button = new Button(s, *AssetLoader<sf::Font>::GetInstance().Get("C:/Windows/Fonts/SegoeUI.ttf"), pos);
	button->setCallback(callback);
	objects.push_back(button);
}

void PlayGui::addButton(Button * button)
{
	objects.push_back(button);
}

