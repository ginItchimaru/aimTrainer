#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	this->window = nullptr;

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


void Game::update() {

	this->pollEvents();

	this->updateMousePosition();

	this->target.update(this->window);

}


void Game::render() {

	this->window->clear();

	//Render
	this->target.render(this->window);

	this->window->display();

}
