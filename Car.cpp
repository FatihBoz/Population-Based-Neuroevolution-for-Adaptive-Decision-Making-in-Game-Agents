#include "Car.h"

Car::Car(const sf::Texture& texture, sf::Vector2f startPosition)
	: carSprite(texture), position(startPosition), speed(4), acceleration(0), angle(3.14159), isAlive(true){

	sf::Vector2f originVector(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	carSprite.setOrigin(originVector);
	carSprite.setPosition(position);
}

void Car::update(const TrackPhysic& physics) {
	if (!isAlive) return;

	sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);
	sf::Vector2f nextPos = position + velocity;

	
	if (physics.isOnTrack(nextPos)) {
		position = nextPos;
		carSprite.setPosition(position);
		carSprite.setRotation(sf::radians(static_cast<float>(angle) + 3.14159f / 2.0f));
	} else {
		isAlive = false;
		speed = 0;
		carSprite.setColor(sf::Color::Red);
	}
	
}


void Car::draw(sf::RenderWindow& window) {
	window.draw(carSprite);
}