#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "target.h"


class Game {

private:
	//Variables
	
	//Game logic
	int targetsMax;

	int targetsHit;
	int targetsMissed;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	std::vector<Target> targets;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Private functions
	void initVariables();
	void initWindow();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions	
	void pollEvents();

	void updateMousePosition();
	void spawnTargets();
	void updateTargets();
	void update();
	
	void render();
};
