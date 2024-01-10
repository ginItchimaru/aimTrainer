#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Target {

private:
	float borderLength;
	sf::Vector2f scale;
	int shapeSize;

	sf::Sprite sprite;
	sf::Texture texture;

	void initVariables();
	void initTexture();
	void initTargets(const sf::RenderWindow& window);


public:

	Target(const sf::RenderWindow& window);
	virtual ~Target();

	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;

	void update();
	void render(sf::RenderTarget& target);

};

