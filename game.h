#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "target.h"


class Game {

private:
	//Variables

	//Spawning Targets
	float borderLength;

	//Game logic
	int targetsMax;

	int targetsHit;
	int targetsMissed;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event e;

	std::vector<Target*> targets;

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
	
	bool isTooClose(float x, float y);
	void spawnTargets(sf::RenderWindow& window);
	bool isValidSpawn(float newX, float newY) const;
	
	void updateMousePosition();
	void updateTargets();
	void update();
	
	void render();
};
