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
	this->spawnBorderFullscreenX = 0.f;
	this->spawnBorderFullscreenY = 0.f;

	this->targetGap = 100.f;

	//Mouse
	this->gameStart = true;

	this->mouseSensScale = 1.f;

	//Crosshair
	this->crosshairScale.y = 0.1f;
	this->crosshairScale.x = 0.1f;

	//Game logic
	this->targetsMax = 3;
	this->targetsHit = 0;
	this->targetsMissed = 0;

	this->mouseHeld = false;

}


void Game::initWindow() {

	this->videoMode.height = 800;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "aim trainer", sf::Style::Close);
	this->window->setFramerateLimit(144);

}

void Game::initWorld() {

	if (!this->backgroundTexture.loadFromFile("textures/spaceBackground3000x2000.png"))
		std::cout << "ERROR::GAME::Failed to load background texture" << "\n";

	this->background.setTexture(this->backgroundTexture);
	this->frameBackground = sf::IntRect(1100, 600, 800, 800);
	this->background.setTextureRect(this->frameBackground);

}

void Game::initCrosshair() {
	
	if (!this->crosshairTexture.loadFromFile("textures/crosshair.png"))
		std::cout << "ERROR::GAME::Failed to load crossair texture" << "\n";

	this->crosshair.setTexture(this->crosshairTexture);
	this->crosshair.setScale(this->crosshairScale);

	// make cursor invisible
	this->window->setMouseCursorVisible(false);

}

//Constructors / Destructors
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initCrosshair();

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
					this->frameBackground.left = 540.f;
					this->frameBackground.top = 460.f;
					this->frameBackground.width = 1920.f;
					this->frameBackground.height = 1080.f;
					this->background.setTextureRect(this->frameBackground);

					// mouse
					this->gameStart = true;

					// make cursor invisible
					this->window->setMouseCursorVisible(false);

				}
				else {
					
					// window
					this->window->create(sf::VideoMode(this->videoMode), "aim trainer", sf::Style::Close);
					
					// background
					this->frameBackground.left = 1100.f;
					this->frameBackground.top = 600.f;
					this->frameBackground.width = 800.f;
					this->frameBackground.height = 800.f;
					this->background.setTextureRect(this->frameBackground);

					// mouse
					this->gameStart = true;

					// make cursor invisible
					this->window->setMouseCursorVisible(false);

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

void Game::updateMouse() {

	// int
	this->mousePos = sf::Mouse::getPosition(*this->window);
	// float
	this->mousePosFloat = this->window->mapPixelToCoords(this->mousePos);

	if (this->gameStart) {

		sf::Mouse::setPosition(sf::Vector2i(this->frameBackground.width / 2, this->frameBackground.height / 2), *this->window);
		this->gameStart = false;

	}

	sf::Vector2i defaultMousePos = sf::Mouse::getPosition(*this->window);

	std::cout << "x: " << this->mousePos.x << " y: " << this->mousePos.y << "\n";

	this->mousePosFloat = this->window->mapPixelToCoords(this->mousePos);

}

void Game::updateCrosshair() {

	// set crosshair position
	this->crosshairPosX = static_cast<float>(this->frameBackground.width / 2) - this->crosshair.getGlobalBounds().width / 2;
	this->crosshairPosY = static_cast<float>(this->frameBackground.height / 2) - this->crosshair.getGlobalBounds().height / 2;

	this->crosshair.setPosition(this->crosshairPosX, this->crosshairPosY);

	// move background and targets
	// in contrast to mouse position
	// to make crosshair work
	if (this->mousePosFloat.x != this->frameBackground.width / 2 || this->mousePosFloat.y != this->frameBackground.height) {

		if (this->mousePosFloat.x < this->frameBackground.width / 2) {
			
			// move background
			float mouseMovedX = this->frameBackground.width / 2 - this->mousePosFloat.x;
			this->frameBackground.left -= mouseMovedX * mouseSensScale;
			
			// background border
			if (this->frameBackground.left < 0.f)
				this->frameBackground.left = 0.f;
			
			// set background texture after its being moved
			this->background.setTextureRect(this->frameBackground);

			// move targets and animation
			if (this->frameBackground.left > 0.f) {

				// targets
				for (size_t i = 0; i < this->targets.size(); i++) {

					float newTargetPosX = this->targets[i]->getPosition().x + (mouseMovedX * 0.9f);
					this->targets[i]->setPosition(newTargetPosX, this->targets[i]->getPosition().y);

				}

				// animations
				for (size_t i = 0; i < this->animations.size(); i++) {

					float newAnimationPosX = this->animations[i]->getPosition().x + (mouseMovedX * 0.9f);
					this->animations[i]->setPosition(newAnimationPosX, this->animations[i]->getPosition().y);

				}

			}
			
			// recentering mouse
			sf::Mouse::setPosition(sf::Vector2i(this->frameBackground.width / 2, this->frameBackground.height / 2), *this->window);

		}
		else if (this->mousePosFloat.x > this->frameBackground.width / 2) {
			
			// move background
			float mouseMovedX = this->mousePosFloat.x - this->frameBackground.width / 2;
			this->frameBackground.left += mouseMovedX * mouseSensScale;
			
			// background border
			if (this->frameBackground.left > 3000.f - this->frameBackground.width)
				this->frameBackground.left = 3000.f - this->frameBackground.width;
			
			// set background texture after its being moved
			this->background.setTextureRect(this->frameBackground);

			// move targets and animation
			if (this->frameBackground.left < 3000.f - this->frameBackground.width) {

				// targets
				for (size_t i = 0; i < this->targets.size(); i++) {

					float newTargetPosX = this->targets[i]->getPosition().x - (mouseMovedX * 0.9f);
					this->targets[i]->setPosition(newTargetPosX, this->targets[i]->getPosition().y);

				}

				// animations
				for (size_t i = 0; i < this->animations.size(); i++) {

					float newAnimationPosX = this->animations[i]->getPosition().x - (mouseMovedX * 0.9f);
					this->animations[i]->setPosition(newAnimationPosX, this->animations[i]->getPosition().y);

				}

			}
			
			// recentering mouse
			sf::Mouse::setPosition(sf::Vector2i(this->frameBackground.width / 2, this->frameBackground.height / 2), *this->window);
		
		}

		if (this->mousePosFloat.y < this->frameBackground.height / 2) {
			
			// move background
			float mouseMovedY = this->frameBackground.height / 2 - this->mousePosFloat.y;
			this->frameBackground.top -= mouseMovedY * mouseSensScale;
			
			// background border
			if (this->frameBackground.top < 0.f)
				this->frameBackground.top = 0.f;
			
			// set background texture after its being moved
			this->background.setTextureRect(this->frameBackground);

			// move targets and animation
			if (this->frameBackground.top > 0.f) {

				// targets
				for (size_t i = 0; i < this->targets.size(); i++) {

					float newTargetPosY = this->targets[i]->getPosition().y + (mouseMovedY * 0.9f);
					this->targets[i]->setPosition(this->targets[i]->getPosition().x, newTargetPosY);

				}

				// animations
				for (size_t i = 0; i < this->animations.size(); i++) {

					float newAnimationPosY = this->animations[i]->getPosition().y + (mouseMovedY * 0.9f);
					this->animations[i]->setPosition(this->animations[i]->getPosition().x, newAnimationPosY);

				}

			}
		
			// recentering mouse
			sf::Mouse::setPosition(sf::Vector2i(this->frameBackground.width / 2, this->frameBackground.height / 2), *this->window);
		
		}
		else if (this->mousePosFloat.y > this->frameBackground.height / 2) {
			
			// move background
			float mouseMovedY = this->mousePosFloat.y - this->frameBackground.height / 2;
			this->frameBackground.top += mouseMovedY * mouseSensScale;
			
			// background border
			if (this->frameBackground.top > 2000.f - this->frameBackground.height)
				this->frameBackground.top = 2000.f - this->frameBackground.height;
		
			// set background texture after its being moved
			this->background.setTextureRect(this->frameBackground);

			// move targets and animation
			if (this->frameBackground.top < 2000.f - this->frameBackground.height) {
				
				// targets
				for (size_t i = 0; i < this->targets.size(); i++) {

					float newTargetPosY = this->targets[i]->getPosition().y - (mouseMovedY * 0.9f);
					this->targets[i]->setPosition(this->targets[i]->getPosition().x, newTargetPosY);

				}

				// animations
				for (size_t i = 0; i < this->animations.size(); i++) {

					float newAnimationPosY = this->animations[i]->getPosition().y - (mouseMovedY * 0.9f);
					this->animations[i]->setPosition(this->animations[i]->getPosition().x, newAnimationPosY);

				}
			
			}
		
			// recentering mouse
			sf::Mouse::setPosition(sf::Vector2i(this->frameBackground.width / 2, this->frameBackground.height / 2), *this->window);
		
		}
	
	}

}

void Game::updateTargetsAndAnimation() {
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
		if (!this->mouseHeld) {

			this->mouseHeld = true;

			for (size_t i = 0; i < this->targets.size(); i++) {

				if (this->targets[i]->getBounds().contains(this->mousePosFloat)) {

					float x = this->targets[i]->getPosition().x;
					float y = this->targets[i]->getPosition().y;
					//float x = this->targets[i]->getSpawnPos().x;
					//float y = this->targets[i]->getSpawnPos().y;

					delete this->targets[i];
					this->targets.erase(this->targets.begin() + i);
					this->targetsHit++;

					this->animations.push_back(new Animation(x, y));

				}
				else {
					this->targetsMissed++;
				
				}

			}

		}

	}
	else {
		this->mouseHeld = false;
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

	this->updateMouse();
	
	this->updateCrosshair();

	this->updateTargetsAndAnimation();

}

void Game::renderWorld() {

	this->window->draw(this->background);

}

void Game::renderCrosshair() {

	this->window->draw(this->crosshair);

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
	
	//Draw crosshair
	this->renderCrosshair();
	
	this->window->display();

}