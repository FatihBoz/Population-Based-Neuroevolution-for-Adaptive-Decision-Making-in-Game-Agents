#include "Simulation.h"

Simulation::Simulation(const std::string& filePath, sf::Vector2f centerStartPosition)
	: centerStartPosition(centerStartPosition) {

	if (!carTexture.loadFromFile(filePath)) {
		throw std::runtime_error("Failed to load car texture: " + filePath);
	}
	setupCheckpoints();
}

void Simulation::startNewGeneration(int carCount) {
	cars.clear();

	for (int i = 0; i < carCount; ++i) {
		cars.push_back(Car(carTexture, sf::Vector2f(centerStartPosition.x, centerStartPosition.y)));
	}
}

void Simulation::updateAll(const TrackPhysic& physics) {
	for (auto& car : cars) {
		car.update(physics, checkPoints);
		car.checkCheckpoint(checkPoints);
	}
}

void Simulation::drawAll(sf::RenderWindow& window) {
	for (auto& car : cars) {
		car.draw(window);
	}

	for (auto& cp : checkPoints) {
		window.draw(cp.visualRect);
	}

}

bool Simulation::isGenerationDead() {
	for (const auto& car : cars) {
		if (car.isAlive()) return false;
	}
	return true;
}

void Simulation::nextGeneration() {

    float maxFitness = -1.0f;
    int bestIndex = 0;

    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i].getFitness() > maxFitness) {
            maxFitness = cars[i].getFitness();
            bestIndex = i;
        }
    }

    NeuralNetwork bestBrain = cars[bestIndex].brain;


    int popSize = cars.size();
    cars.clear();

    for (int i = 0; i < popSize; ++i) {
        Car newCar(carTexture, sf::Vector2f(centerStartPosition.x, centerStartPosition.y));

        if (i == 0) {
            //First car is the same as champion
            newCar.brain = bestBrain;
        }
        else {
            NeuralNetwork mutatedBrain = bestBrain;
            mutatedBrain.reseed();
            mutatedBrain.mutate(0.05f);
            newCar.brain = mutatedBrain;
        }

        cars.push_back(newCar);
    }

    generationCount++;
}

void Simulation::setupCheckpoints() {
    checkPoints.clear();

    checkPoints.push_back(Checkpoint(sf::Vector2f(1250, 120), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(850, 120), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(450, 120), sf::Vector2f(100, 200)));

    checkPoints.push_back(Checkpoint(sf::Vector2f(220, 320), sf::Vector2f(200, 100)));

    checkPoints.push_back(Checkpoint(sf::Vector2f(450, 440), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(850, 440), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(1250, 440), sf::Vector2f(100, 200)));

    checkPoints.push_back(Checkpoint(sf::Vector2f(1610, 640), sf::Vector2f(200, 100)));

    checkPoints.push_back(Checkpoint(sf::Vector2f(1250, 760), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(850, 760), sf::Vector2f(100, 200)));
    checkPoints.push_back(Checkpoint(sf::Vector2f(450, 760), sf::Vector2f(100, 200)));
}

void Simulation::restart() {
    int currentCount = cars.size();
    if (currentCount == 0) currentCount = 10;
    generationCount = 1;
    startNewGeneration(currentCount);
}