#include "Simulation.h"

Simulation::Simulation(const std::string& filePath, sf::Vector2f centerStartPosition)
	: centerStartPosition(centerStartPosition) {

	if (!carTexture.loadFromFile(filePath)) {
		throw std::runtime_error("Failed to load car texture: " + filePath);
	}
}

void Simulation::startNewGeneration(int carCount) {
	cars.clear();

	for (int i = 0; i < carCount; ++i) {
		cars.push_back(Car(carTexture, sf::Vector2f(centerStartPosition.x, centerStartPosition.y + (32 * i))));
	}
}

void Simulation::updateAll(const TrackPhysic& physics) {
	for (auto& car : cars) {
		car.update(physics);
	}
}

void Simulation::drawAll(sf::RenderWindow& window) {
	for (auto& car : cars) {
		car.draw(window);
	}

}