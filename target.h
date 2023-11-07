#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Target {

private:
	float borderLength;

	std::vector<sf::CircleShape> circleShapes;
	sf::CircleShape circleShape;

	void initVariables();
	void initTargets(const sf::RenderWindow& window);


public:

	Target(const sf::RenderWindow& window);
	virtual ~Target();

	const sf::CircleShape getShape() const;

	void update();
	void render(sf::RenderTarget& target);

};

