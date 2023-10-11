#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game {

private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	int maxTargets;

	//Game objects
	std::vector<sf::RectangleShape> targets;
	sf::RectangleShape target;

	//Private functions
	void initVariables();
	void initWindow();
	void initTargets();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnTarget();
	
	void pollEvents();
	void updateMousePosition();
	void updateTargets();
	void update();
	
	void renderTargets(sf::RenderTarget& target);
	void render();
};
