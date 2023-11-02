#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	this->window = nullptr;

	//Game logic
	this->targetsMax = 10;

	this->targetsHit = 0;
	this->targetsMissed = 0;

}

void Game::initWindow() {

	this->videoMode.height = 800;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "aim trainer", sf::Style::Titlebar | sf::Style::Close);
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
	while (this->window->pollEvent(this->event)) {

		switch (this->event.type) {

		case sf::Event::Closed:		// to close the game when user closes window
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}

}


void Game::updateMousePosition() {

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);	// mouse pos as integer
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);	// mouse pos as float
	std::cout << "y: " << this->mousePosWindow.y << " x: " << mousePosWindow.x << "\n";

}

void Game::spawnTargets() {

	if (this->targets.size() < this->targetsMax) {

		this->targets.push_back(Target(*this->window));

	}

}


void Game::updateTargets() {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		bool deleted = false;
		for (size_t i = 0; i < this->targets.size() and deleted == false; i++) {

			if (this->targets[i].getRadius(this->mousePosView)) {
				


			}

		}

	}

}






void Game::update() {

	this->pollEvents();

	this->spawnTargets();

	this->updateMousePosition();

}


void Game::render() {

	this->window->clear();

	//Render
	for (auto i : this->targets) {

		i.render(*this->window);

	}
	this->window->display();

}
