#pragma once
#include <SFML/Graphics.hpp>
#include "TrackPhysic.h"
#include "NeuralNetwork.h"
#include "Checkpoint.h"

class Car {

private:
	sf::Sprite carSprite;
	sf::Vector2f position;
	double speed;
	double acceleration;
	double angle;
	bool alive;
	float fitnessScore;
	int nextCheckpointIndex;
	int framesAlive;

	//Sensor data
	float maxRayDistance = 150.0f;
	std::vector<float> rayAngles = { -90.0f , -45.0f, 0.0f, 45.0f, 90.0f };

	std::vector<sf::Vector2f> rayHitPoints; //for visual debugging

public:
	NeuralNetwork brain;

	Car(const sf::Texture& texture, sf::Vector2f startPosition);
	void update(const TrackPhysic& physics, const std::vector<Checkpoint>& checkpoints);
	void draw(sf::RenderWindow& window);

	std::vector<float> getNormalizedInputs(const TrackPhysic& physics);
	void checkCheckpoint(const std::vector<Checkpoint>& checkpoints);
	float getFitness() const { return fitnessScore; }
	bool isAlive() const { return alive; }
};	



