#include "animation.h"
#include<iostream>

void Animation::initVariables() {



}

void Animation::initTexture() {

	if (!this->texture.loadFromFile("textures/animation.png")) {

		std::cout << "ERROR::ANIMATION::INITTEXTURE::Could not load texture file." << "\n";

	}

}

void Animation::initSprite() {

	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 256, 64, 64);

	this->sprite.setTextureRect(this->currentFrame);
	//this->sprite.setScale(1, 1);

}

void Animation::initAnimations() {

	this->animationTimer.restart();

}

Animation::Animation(float x, float y) {

	//this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();

	this->sprite.setPosition(x, y);

}

Animation::~Animation() {



}

const bool Animation::animationOver() const {
	
	return this->animationFinished;
	
}

void Animation::updateAnimations() {
	
	this->animationFinished = false;

	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {

		this->currentFrame.left += 64.f;
		if (this->currentFrame.left >= 576.f) {
			
			this->currentFrame.left = 0.f;
			this->animationFinished = true;

		}
			

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);

	}

}

void Animation::update() {

	this->updateAnimations();

}

void Animation::render(sf::RenderTarget& target) {

	target.draw(this->sprite);

}