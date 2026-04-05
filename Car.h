#pragma once
#include <SFML/Graphics.hpp>
#include "TrackPhysic.h"

class Car {

private:
	sf::Sprite carSprite;
	sf::Vector2f position;
	double speed;
	double acceleration;
	double angle;
	bool isAlive;

public:
	Car(const sf::Texture& texture, sf::Vector2f startPosition);
	void update(const TrackPhysic& physics);
	void draw(sf::RenderWindow& window);

};	



