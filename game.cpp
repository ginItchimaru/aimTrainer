#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	// window
	this->window = nullptr;
	this->fullscreen = false;

	//Spawning targets
	this->borderLength = 250.f;
	this->borderLengthFullscreen = this->borderLength * 3;

	//Game logic
	this->targetsMax = 3;

	this->targetsHit = 0;
	this->targetsMissed = 0;

}

void Game::initWindow() {

	this->videoMode.height = 800;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "aim trainer", sf::Style::Close);
	this->window->setFramerateLimit(144);

}

void Game::initWorld() {

	if (!this->backgroundTextureSmall.loadFromFile("textures/spaceBackgroundSmall.png"))
		std::cout << "ERROR::GAME::Failed to load small background texture" << "\n";

	if (!this->backgroundTextureBig.loadFromFile("textures/spaceBackgroundBig.png"))
		std::cout << "ERROR::GAME::Failed to load big background texture" << "\n";

	this->background.setTexture(this->backgroundTextureBig);
	this->frameBackground = sf::IntRect(560, 140, 800, 800);
	this->background.setTextureRect(this->frameBackground);

}

//Constructors / Destructors
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initWorld();

}

Game::~Game() {

	delete this->window;

}

//Accessors
const bool Game::running() const {

	return this->window->isOpen();

}

//Public Functions
void Game::pollEvents() {

	static bool switchTexture = false;

	//Event polling
	while (this->window->pollEvent(this->e)) {

		switch (this->e.type) {

		case sf::Event::Closed:		// to close the game when user closes window
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->e.key.code == sf::Keyboard::Escape)
				this->window->close();
			// fullscreen option
			else if (this->e.key.code == sf::Keyboard::F) {
				
				this->fullscreen = !this->fullscreen;
				
				if (this->fullscreen) {
					
					this->window->create(sf::VideoMode(1920, 1080), "aim trainer", sf::Style::Fullscreen);
					
					this->frameBackground.left = 0.f;
					this->frameBackground.top = 0.f;
					this->frameBackground.width = 1920.f;
					this->frameBackground.height = 1080.f;
					this->background.setTextureRect(this->frameBackground);

				}
				else {
				
					this->window->create(sf::VideoMode(this->videoMode), "aim trainer", sf::Style::Close);
					
					this->frameBackground.left = 560.f;
					this->frameBackground.top = 140.f;
					this->frameBackground.width = 800.f;
					this->frameBackground.height = 800.f;
					this->background.setTextureRect(this->frameBackground);

				}
			
			}
			break;
		
		}
	
	}

}

void Game::spawnTargets(sf::RenderWindow& window) {
	
	// add border
	float minX, maxX, minY, maxY;

	if (!this->fullscreen) {
		
		minX = this->borderLength;
		maxX = window.getSize().x - this->borderLength;
		minY = this->borderLength;
		maxY = window.getSize().y - this->borderLength;
	
	}
	else if (this->fullscreen) {
		
		minX = this->borderLength;
		maxX = window.getSize().x - this->borderLengthFullscreen;
		minY = this->borderLength;
		maxY = window.getSize().y - this->borderLengthFullscreen;
	
	}

	float randX, randY;

	if (this->targets.size() < this->targetsMax) {

		do {

			randX = static_cast<float>(rand() % static_cast<int>(maxX - minX + 1) + minX);
			randY = static_cast<float>(rand() % static_cast<int>(maxY - minY + 1) + minY);

		} while (!isValidSpawn(randX, randY));

		this->targets.push_back(new Target(randX, randY));

	}

}

bool Game::isValidSpawn(float newX, float newY) const {
	
	// Check if the new target is at least 50 units apart from the previous ones
	for (const auto& target : this->targets) {
		
		float distance = std::sqrt(std::pow(newX - target->getBounds().left, 2) + std::pow(newY - target->getBounds().top, 2));
		
		if (distance < 50.0f) {
			
			return false;
		
		}
	
	}

	return true;

}

void Game::updateMousePosition() {

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);	// mouse pos as integer
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);	// mouse pos as float
	//std::cout << "y: " << this->mousePosWindow.y << " x: " << mousePosWindow.x << "\n";

}

void Game::updateTargetsAndAnimation() {
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
		for (size_t i = 0; i < this->targets.size(); i++) { 
	
			if (this->targets[i]->getBounds().contains(this->mousePosView)) {
				
				float x = this->targets[i]->getPosition().x;
				float y = this->targets[i]->getPosition().y;

				delete this->targets[i];
				this->targets.erase(this->targets.begin() + i);
				this->targetsHit++;
				
				this->animations.push_back(new Animation(x, y));
			
			} else {
				
				this->targetsMissed++;
			
			}
		
		}
	
	}

	for (auto* animation : this->animations) {

		animation->update();

	}

}

void Game::update() {

	this->pollEvents();

	this->spawnTargets(*this->window);

	this->updateMousePosition();

	this->updateTargetsAndAnimation();

	for (auto* animation : this->animations) {

		animation->update();

	}

}

void Game::renderWorld() {

	this->window->draw(this->background);

}

void Game::render() {

	this->window->clear();

	//Draw world
	this->renderWorld();

	//Render
	for (auto *target : this->targets) {

		target->render(*this->window);

	}

	for (auto *animation : this->animations) {

		animation->render(*this->window);

	}
	
	this->window->display();

}
