#include "game.h"
#include <iostream>


//Private functions
void Game::initVariables() {

	// window
	this->window = nullptr;
	this->fullscreen = false;

	//Spawning targets
	this->spawnBorderY = 200.f;
	this->spawnBorderX = 250.f;
	this->spawnBorderFullscreenY = 200.f;
	this->spawnBorderFullscreenX = 500.f;

	this->targetGap = 100.f;

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

	if (!this->backgroundTexture.loadFromFile("textures/spaceBackgroundBig.png"))
		std::cout << "ERROR::GAME::Failed to background texture" << "\n";

	this->background.setTexture(this->backgroundTexture);
	this->frameBackground = sf::IntRect(560, 140, 800, 800);
	this->background.setTextureRect(this->frameBackground);

}

void Game::initCursor() {

	if (!this->cursorTexture.loadFromFile("textures/Lava.png"))	// needs texture
		std::cout << "ERROR::GAME::Failed to load cursor texture" << "\n";

	// convert texture to pixels according to chatgpt
	sf::Image image = this->cursorTexture.copyToImage();
	const sf::Uint8* pixels = image.getPixelsPtr();

	// hide system cursor
	this->window->setMouseCursorVisible(false);

	if (cursor.loadFromPixels(pixels, this->cursorTexture.getSize(), { 0, 0 })) {
		// Set the cursor
		this->window->setMouseCursor(cursor);
	}
	else {	
		std::cout << "ERROR::GAME::Failed to create cursor" << "\n";
	}

}

//Constructors / Destructors
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initCursor();

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

	this->changedScreen = false;

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
				this->changedScreen = true;
				
				if (this->fullscreen) {
					
					// window
					this->window->create(sf::VideoMode::getDesktopMode(), "aim trainer", sf::Style::Fullscreen);
					
					// background
					this->frameBackground.left = 0.f;
					this->frameBackground.top = 0.f;
					this->frameBackground.width = 1920.f;
					this->frameBackground.height = 1080.f;
					this->background.setTextureRect(this->frameBackground);

				}
				else {

					// window
					this->window->create(sf::VideoMode(this->videoMode), "aim trainer", sf::Style::Close);
					
					// background
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
	float minX = 0.f;
	float maxX = 0.f;
	float minY = 0.f;
	float maxY = 0.f;

	if (!this->fullscreen) {

		minX = this->spawnBorderX;
		maxX = window.getSize().x - this->spawnBorderX;
		minY = this->spawnBorderY;
		maxY = window.getSize().y - this->spawnBorderY;

	}
	else {

		minX = this->spawnBorderFullscreenX;
		maxX = window.getSize().x - this->spawnBorderFullscreenX;
		minY = this->spawnBorderFullscreenY;
		maxY = window.getSize().y - this->spawnBorderFullscreenY;

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
		
		if (distance < this->targetGap) {
			
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

	if (this->changedScreen) {
		
		this->changedScreen = false;

		for (size_t i = 0; i < this->targets.size(); /* no increment here */) {
			
			if (!this->fullscreen) {
				// Check if the target is outside the valid spawn range
				if (this->targets[i]->getPosition().x > this->window->getSize().x - this->spawnBorderX ||
					this->targets[i]->getPosition().y > this->window->getSize().y - this->spawnBorderY) {
					
					delete this->targets[i];
					this->targets.erase(this->targets.begin() + i);
				
				}
				else {
					// Only increment when not erasing a target
					++i;
				}
			
			}
			else {
				// Handle deletion for fullscreen (windowed targets are already deleted)
				delete this->targets[i];
				this->targets.erase(this->targets.begin() + i);
			
			}
		
		}
	
	}

	for (auto* animation : this->animations) {

		animation->update();

	}
	
	for (size_t i = 0; i < this->animations.size(); ++i) {
		
		if (this->animations[i]->animationOver()) {
		
			delete this->animations[i];
			this->animations.erase(this->animations.begin() + i);
			
			--i;
		}
		
	}

}

void Game::update() {
	
	this->pollEvents();

	this->spawnTargets(*this->window);

	this->updateMousePosition();

	this->updateTargetsAndAnimation();

}

void Game::renderWorld() {

	this->window->draw(this->background);

}

void Game::render() {

	this->window->clear();

	//Draw world
	this->renderWorld();

	//Render
	for (auto *animation : this->animations) {

		animation->render(*this->window);

	}

	for (auto *target : this->targets) {

		target->render(*this->window);

	}
	
	this->window->display();

}