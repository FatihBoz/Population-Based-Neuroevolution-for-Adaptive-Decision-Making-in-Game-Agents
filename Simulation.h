#pragma once
#include <vector>
#include "Car.h"
#include "TrackPhysic.h"

class Simulation {
private:
	sf::Texture carTexture;
	std::vector<Car> cars;
	sf::Vector2f centerStartPosition;
public:
	Simulation(const std::string& filePath, sf::Vector2f centerStartPosition);
	void startNewGeneration(int carCount);
	void updateAll(const TrackPhysic& physics);
	void drawAll(sf::RenderWindow& window);
};