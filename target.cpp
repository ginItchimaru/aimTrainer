#include "target.h"
#include<iostream>

void Target::initVariables() {

	this->borderLength = 200.f;
	this->scale.x = 1.f;
	this->scale.y = 1.f;

}

void Target::initTexture() {

	if (!this->texture.loadFromFile("textures/Lava.png")) {

		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";

	}

}

void Target::initTargets(const sf::RenderWindow& window) {
	
	// randomize where the shapes spawn on the screen
	// making sure it doesnt spawn to close to the windwo border
	float minX = this->borderLength + this->sprite.getGlobalBounds().left;
	float maxX = window.getSize().x - this->borderLength - this->sprite.getGlobalBounds().left;
	float minY = this->borderLength + this->sprite.getGlobalBounds().top;
	float maxY = window.getSize().y - this->borderLength - this->sprite.getGlobalBounds().top;
	
	float randX = static_cast<float>(rand() % static_cast<int>(maxX - minX + 1) + minX);  // second static_cast needs to be int so it can be converted to float
	float randY = static_cast<float>(rand() % static_cast<int>(maxX - minX + 1) + minX);

	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(randX, randY);
	this->sprite.setScale(this->scale);

}

Target::Target(const sf::RenderWindow& window) {
	
	this->initVariables();
	this->initTexture();
	this->initTargets(window);

}

Target::~Target() {



}

const sf::FloatRect Target::getBounds() const {

	return this->sprite.getGlobalBounds();

}

const sf::Vector2f Target::getPosition() const {

	return this->sprite.getPosition();

}

void Target::update() {



}

void Target::render(sf::RenderTarget& target) {

	target.draw(this->sprite);

}
