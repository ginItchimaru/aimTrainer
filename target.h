#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Target {

private:
	
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

	void update();
	void render(sf::RenderTarget& target);

};

