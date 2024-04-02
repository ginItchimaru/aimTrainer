#include "target.h"
#include<iostream>

void Target::initVariables() {

	this->scale.x = 1.f;
	this->scale.y = 1.f;

}

void Target::initTexture() {

	if (!this->texture.loadFromFile("textures/iceTarget.png")) {

		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";

	}

}

void Target::initTarget() {

	this->sprite.setTexture(this->texture);
	this->sprite.setScale(this->scale);

}

Target::Target(float x, float y) {
	
	this->initVariables();
	this->initTexture();
	this->initTarget();

	this->sprite.setPosition(x, y);
	this->spawnPosX = x;
	this->spawnPosY = y;

}

Target::~Target() {



}

const sf::FloatRect Target::getBounds() const {

	return this->sprite.getGlobalBounds();

}

const sf::Vector2f Target::getPosition() const {

	return this->sprite.getPosition();

}

const sf::Vector2f Target::getSpawnPos() const {

	return sf::Vector2f(this->spawnPosX, this->spawnPosY);

}

void Target::setPosition(float x, float y) {

	this->sprite.setPosition(x, y);

}

void Target::update() {



}

void Target::render(sf::RenderTarget& target) {

	target.draw(this->sprite);

}