#include "target.h"

void Target::initVariables() {

	this->borderLength = 50;

}

void Target::initTargets(const sf::RenderWindow& window) {
	
	// randomize where the shapes spawn on the screen
	// making sure it doesnt spawn to close to the windwo border
	float minX = this->borderLength + this->circleShape.getRadius();
	float maxX = window.getSize().x - this->borderLength - this->circleShape.getRadius();
	float minY = this->borderLength + this->circleShape.getRadius();
	float maxY = window.getSize().y - this->borderLength - this->circleShape.getRadius();
	
	float randX = static_cast<float>(rand() % static_cast<int>(maxX - minX + 1) + minX);  // second static_cast needs to be int so it can be converted to float
	float randY = static_cast<float>(rand() % static_cast<int>(maxX - minX + 1) + minX);

	this->circleShape.setRadius(10.f);
	sf::Color color(255, 0, 0);
	this->circleShape.setFillColor(color);
	this->circleShape.setPosition(sf::Vector2f(randX, randY));

}

Target::Target(const sf::RenderWindow& window) {
	
	this->initVariables();
	this->initTargets(window);

}

Target::~Target() {



}

const sf::CircleShape Target::getShape() const {

	return this->circleShape;

}

void Target::update() {



}

void Target::render(sf::RenderTarget& target) {

	target.draw(this->circleShape);

}
