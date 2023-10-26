#include "target.h"

void Target::initVariables() {



}

void Target::initTargets(const sf::RenderWindow& window) {

	this->circleShape.setRadius(10.f);
	sf::Color color(255, 0, 0);
	this->circleShape.setFillColor(color);
	this->circleShape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % window.getSize().x - this->circleShape.getGlobalBounds().width),
			static_cast<float>(rand() % window.getSize().y - this->circleShape.getGlobalBounds().height)
		)
	);

}

Target::Target(const sf::RenderWindow& window) {
	
	this->initVariables();
	this->initTargets(window);

}

Target::~Target() {



}

void Target::update(sf::RenderTarget* target) {



}

void Target::render(sf::RenderTarget* target) {



}
