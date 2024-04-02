#pragma once

#include"target.h"


class Animation {

private:
	bool animationFinished;

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
	
	//Accessors
	const sf::Vector2f getPosition() const;

	//Mutators
	void setPosition(float x, float y);

	const bool animationOver() const;

	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);

};

