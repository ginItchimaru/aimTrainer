#include "target.h"

void target::initVariables() {



}

void target::initTargets() {

	this->targetRect.setPosition(100.f, 100.f);
	this->targetRect.setSize(sf::Vector2f(50.f, 50.f));
	this->targetRect.setFillColor(sf::Color::Red);

}

target::target() {
	
	this->initVariables();
	this->initTargets();

}

target::~target() {



}
