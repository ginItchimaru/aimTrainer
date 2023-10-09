#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	this->window = nullptr;

	//Game logic
	this->maxTargets = 10;
}

void Game::initWindow() {

	this->videoMode.height = 800;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "aim trainer", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initTargets() {

	this->target.setPosition(100.f, 100.f);
	this->target.setSize(sf::Vector2f(50.f, 50.f));
	this->target.setFillColor(sf::Color::Red);
}


//Constructors / Destructors
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initTargets();
}

Game::~Game() {

	delete this->window;
}


//Accessors
const bool Game::running() const {

	return this->window->isOpen();
}


void Game::spawnTarget() {
	// randomizing spawn between window size and object size for x and y
	this->target.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->target.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->target.getSize().y))
	);

	//Spawning the target
	this->targets.push_back(this->target);
}

//Functions
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


//Update
void Game::updateMousePosition() {

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);	// mouse pos as integer
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);	// mouse pos as float
}

void Game::updateTargets() {

	if (this->targets.size() < this->maxTargets) {

		this->spawnTarget();
	}


}

void Game::update() {

	this->pollEvents();

	this->updateMousePosition();

	this->updateTargets();
}


//Render
void Game::renderTargets() {

	//Rendering all the targets
	for (auto& e : this->targets) {

		this->window->draw(e);
	}
}

void Game::render() {

	this->window->clear();

	//Draw game objects
	this->renderTargets();

	this->window->display();
}
