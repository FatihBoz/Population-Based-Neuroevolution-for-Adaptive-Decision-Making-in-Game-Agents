#pragma once
#include <vector>
#include "Car.h"
#include "TrackPhysic.h"
#include "Checkpoint.h"

class Simulation {
private:
	int generationCount = 1;
	sf::Texture carTexture;
	std::vector<Car> cars;
	sf::Vector2f centerStartPosition;
	std::vector<Checkpoint> checkPoints;

public:
	Simulation(const std::string& filePath, sf::Vector2f centerStartPosition);
	void startNewGeneration(int carCount);
	void updateAll(const TrackPhysic& physics);
	void drawAll(sf::RenderWindow& window);
	void nextGeneration();
	void setupCheckpoints();
	bool isGenerationDead();
};