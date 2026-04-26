#pragma once

#include <SFML/Graphics.hpp>

class Checkpoint {

public:
	sf::FloatRect bounds;
	sf::RectangleShape visualRect;
	Checkpoint(sf::Vector2f position, sf::Vector2f size) {
		bounds = sf::FloatRect(position, size);
		visualRect.setPosition(position);
		visualRect.setSize(size);
		visualRect.setFillColor(sf::Color(0, 255, 0, 100));
		visualRect.setOutlineThickness(1.0f);
		visualRect.setOutlineColor(sf::Color::Green);
	}
};