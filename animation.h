#pragma once

#include"target.h"


class Animation {

private:

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock animationTimer;
	sf::IntRect currentFrame;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:

	Animation(float x, float y);
	~Animation();

	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);

};

