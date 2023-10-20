#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Target {

private:
	std::vector<sf::RectangleShape> targetRects;
	sf::RectangleShape targetRect;

	void initVariables();
	void initTargets();


public:
	Target();
	virtual ~Target();

	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

