#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Target {

private:
	float spawnPosX;
	float spawnPosY;
	
	sf::Vector2f scale;
	int shapeSize;

	sf::Sprite sprite;
	sf::Texture texture;

	void initVariables();
	void initTexture();
	void initTarget();


public:
	Target(float x, float);
	~Target();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;

	//Mutators
	void setPosition(float x, float y);

	void update();
	void render(sf::RenderTarget& target);

};