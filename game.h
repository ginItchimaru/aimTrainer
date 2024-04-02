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
	bool changedScreen;
	
	sf::Clock delay; // not in use

	//World
	sf::Texture backgroundTexture;
	sf::Sprite  background;
	sf::IntRect frameBackground;

	//Spawning Targets
	float spawnBorderX;
	float spawnBorderY;
	float spawnBorderFullscreenX;
	float spawnBorderFullscreenY;
	float targetGap;

	//Crossair
	sf::Texture crosshairTexture;
	sf::Sprite  crosshair;
	sf::Vector2f crosshairScale;
	float crosshairPosX;
	float crosshairPosY;

	//Mouse
	sf::Vector2i mousePos;
	sf::Vector2f mousePosFloat;

	bool gameStart;
	bool mouseHeld;
	
	float mouseSensScale;

	//Game logic
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



	//Private functions
	void initVariables();
	void initWindow();
	void initWorld();
	void initCrosshair();

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
	
	void updateMouse();
	void updateCrosshair();
	void updateTargetsAndAnimation();
	void update();
	
	void renderWorld();
	void renderCrosshair();
	void render();
};