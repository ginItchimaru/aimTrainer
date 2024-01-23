#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "target.h"
#include "animation.h"


class Game {

private:
	//Variables
	bool fullscreen;
	
	sf::Clock delay; // not in use

	//World
	sf::Texture backgroundTextureSmall;
	sf::Texture backgroundTextureBig;
	sf::Sprite  background;
	sf::IntRect frameBackground;

	//Spawning Targets
	float borderLength;
	float borderLengthFullscreen;

	//Game logic / Targets
	int targetsMax;
	int targetsHit;
	int targetsMissed;
	
	std::vector<Target*> targets;

	//Animation Effect
	std::vector<Animation*> animations;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event e;


	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Private functions
	void initVariables();
	void initWorld();
	void initWindow();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions	
	void pollEvents();
	
	void spawnTargets(sf::RenderWindow& window);
	bool isValidSpawn(float newX, float newY) const;
	
	void updateMousePosition();
	void updateTargetsAndAnimation();
	void update();
	
	void renderWorld();
	void render();
};
