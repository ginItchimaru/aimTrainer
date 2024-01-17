#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	// window
	this->window = nullptr;
	this->fullscreen = false;

	//Spawning targets
	this->borderLength = 250.f;

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

//Constructors / Destructors
Game::Game() {

	this->initVariables();
	this->initWindow();

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
					
					this->window->create(sf::VideoMode::getDesktopMode(), "aim trainer", sf::Style::Fullscreen);
				
				}
				else {
				
					this->window->create(sf::VideoMode(this->videoMode), "aim trainer", sf::Style::Close);
				
				}
			
			}
			break;
		
		}
	
	}
	
}

bool Game::isTooClose(float x, float y) {	// not in use

	const float minDistance = 50.f;

	for (const auto& target : this->targets) {

		float distance = std::sqrt(std::pow(x - target->getPosition().x, 2) +
								   std::pow(y - target->getPosition().y, 2));

		if (distance < minDistance) {

			return true;

		}

	}

	return false;

}

void Game::spawnTargets(sf::RenderWindow& window) {
	
	// add border
	float minX = this->borderLength;
	float maxX = window.getSize().x - this->borderLength;
	float minY = this->borderLength;
	float maxY = window.getSize().y - this->borderLength;

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

void Game::updateTargets() {
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
		  
		for (size_t i = 0; i < this->targets.size(); i++) { 
	
			if (this->targets[i]->getBounds().contains(this->mousePosView)) {
			
				delete this->targets[i];
				this->targets.erase(this->targets.begin() + i);
				this->targetsHit++;
			
			} else {
				
				this->targetsMissed++;
			
			}
		
		}
	
	}

}

void Game::update() {

	this->pollEvents();

	this->spawnTargets(*this->window);

	this->updateMousePosition();

	this->updateTargets();

}


void Game::render() {

	this->window->clear();

	//Render
	for (auto *target : this->targets) {

		target->render(*this->window);

	}
	
	this->window->display();

}
