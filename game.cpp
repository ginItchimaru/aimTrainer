#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	this->window = nullptr;

	//Game logic
	this->maxTargets = 5;

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
		0.f
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
	std::cout << "y: " << this->mousePosWindow.y << " x: " << mousePosWindow.x << "\n";

}

void Game::updateTargets() {

	if (this->targets.size() < this->maxTargets) {
		this->spawnTarget();
	}

	//bool moveDown = false;
	bool moveUp = false;
	for (int i = 0; i < this->targets.size(); i++) {
		bool deleted = false;

		if (!moveUp) {
			this->targets[i].move(0.f, 3.f);
		}

		//Checking for left mouse button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//Checking if mouse is on the object while clicked
			if (this->targets[i].getGlobalBounds().contains(this->mousePosView)) {

				deleted = true;
			}		
		}

		if (this->targets[i].getPosition().y > this->window->getSize().y) {
			//deleted = true;
			moveUp = true;
		}

		if (moveUp) {
			this->targets[i].move(0.f, -1.f);

			if (this->targets[i].getPosition().y < 150.f) {

				moveUp = false;
			}
		}


		//Deleting object
		if (deleted) {
			this->targets.erase(this->targets.begin() + i);
			//i--;
		}
	}

}

void Game::update() {

	this->pollEvents();

	this->updateMousePosition();

	this->updateTargets();

}


//Render
void Game::renderTargets(sf::RenderTarget& target) {

	//Rendering all the targets
	for (auto& e : this->targets) {
		target.draw(e);
	}

}

void Game::render() {

	this->window->clear();

	//Draw game objects
	this->renderTargets(*this->window);

	this->window->display();

}
