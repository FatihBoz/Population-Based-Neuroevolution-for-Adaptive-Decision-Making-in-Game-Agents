#include "Car.h"
#include <iostream>

Car::Car(const sf::Texture& texture, sf::Vector2f startPosition)
	: carSprite(texture), position(startPosition), speed(4), acceleration(0), angle(3.14159),
	  alive(true), fitnessScore((rand() % 100) / 1000.0f), brain(5,8,2),
	  nextCheckpointIndex(0), framesAlive(0) {

	sf::Vector2f originVector(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	carSprite.setOrigin(originVector);
	carSprite.setPosition(position);
}

void Car::update(const TrackPhysic& physics, const std::vector<Checkpoint>& checkpoints) {
	if (!alive) return;

	framesAlive++;

	if (framesAlive > 300) {
		carSprite.setColor(sf::Color::Red);
		alive = false;
		return;
	}

	// Sense
	std::vector<float> inputs = getNormalizedInputs(physics);

	// Think
	std::vector<float> decisions = brain.feedForward(inputs);

	float steering = decisions[0];
	float throttle = decisions[1];

	// Direksiyonu çevir - Her frame maksimum 0.1 radyan dönebilir
	float turnSpeed = 0.1f;
	angle += steering * turnSpeed;

	// Gaza bas (Hızımız 1.0 ile 5.0 arasında değişsin)
	speed = 1.0f + (throttle * 4.0f);

	sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);
	sf::Vector2f nextPos = position + velocity;

	if (std::isnan(nextPos.x) || std::isnan(nextPos.y) || !physics.isOnTrack(nextPos) || framesAlive > 300) {
		alive = false;
		speed = 0;
		carSprite.setColor(sf::Color::Red);
		
		if (nextCheckpointIndex < checkpoints.size()) {
			const Checkpoint& target = checkpoints[nextCheckpointIndex];

			float targetCenterX = target.bounds.position.x + (target.bounds.size.x / 2.0f);
			float targetCenterY = target.bounds.position.y + (target.bounds.size.y / 2.0f);

			float distToTarget = std::sqrt(std::pow(position.x - targetCenterX, 2) + std::pow(position.y - targetCenterY, 2));
			float bonus = 1000.0f / (distToTarget + 1.0f);

			fitnessScore += bonus;
		}
	}
	else { // Move car
		position = nextPos;
		carSprite.setPosition(position);
		carSprite.setRotation(sf::radians(static_cast<float>(angle) + 3.14159f / 2.0f));

		if (nextCheckpointIndex < checkpoints.size()) {
			if (carSprite.getGlobalBounds().findIntersection(checkpoints[nextCheckpointIndex].bounds)) {
				fitnessScore += 10000.0f;
				nextCheckpointIndex++;
				framesAlive = 0;
			}
		}
	}

	
	
}


void Car::draw(sf::RenderWindow& window) {

	if (alive) {
		for (const auto& hitPoint : rayHitPoints) {
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);
			line[0].position = position;
			line[0].color = sf::Color(sf::Color::Green);
			line[1].position = hitPoint;
			line[1].color = sf::Color::Red;
			window.draw(line);
		}
	}

	window.draw(carSprite);
}


std::vector<float> Car::getNormalizedInputs(const TrackPhysic& physics) {

	std::vector<float> inputs;
	rayHitPoints.clear();

	for (float rayAngle : rayAngles) {

		float angleRad = angle + (rayAngle * 3.14159f / 180.0f);
		//How much distance between car and obstacle in the direction of the ray?
		float distance = physics.getRayDistance(position, angleRad, maxRayDistance);
		inputs.push_back(distance / maxRayDistance); // Normalize to 0-1

		sf::Vector2f hitPoint(position.x + std::cos(angleRad) * distance,position.y + std::sin(angleRad) * distance);
		rayHitPoints.push_back(hitPoint);
	}
	return inputs;
}

void Car::checkCheckpoint(const std::vector<Checkpoint>& checkpoints) {
	if (!alive) return;

	if (nextCheckpointIndex < checkpoints.size()) {

		if (carSprite.getGlobalBounds().findIntersection(checkpoints[nextCheckpointIndex].bounds)) {
			fitnessScore += 1000.0f;
			nextCheckpointIndex++;
			framesAlive = 0;
		}
	}
}
