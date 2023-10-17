#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class target {

private:
	std::vector<sf::RectangleShape> targetRects;
	sf::RectangleShape targetRect;

	void initVariables();
	void initTargets();


public:
	target();
	virtual ~target();

};

