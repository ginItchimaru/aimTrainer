#include "target.h"

void Target::initVariables() {



}

void Target::initTargets() {

	this->targetRect.setPosition(100.f, 100.f);
	this->targetRect.setSize(sf::Vector2f(50.f, 50.f));
	this->targetRect.setFillColor(sf::Color::Red);

}

Target::Target() {
	
	this->initVariables();
	this->initTargets();

}

Target::~Target() {



}

void Target::update(sf::RenderTarget* target) {



}

void Target::render(sf::RenderTarget* target) {



}
