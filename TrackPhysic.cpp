#include "TrackPhysic.h"

TrackPhysic::TrackPhysic(const std::string& path) {
	if (!trackMask.loadFromFile(path)) {
		throw std::runtime_error("Failed to load track mask: " + path);
	}
}

bool TrackPhysic::isOnTrack(sf::Vector2f position) const {
	// Ensure the position is within the bounds of the track mask
	if (position.x < 0 || position.y < 0 || 
		position.x >= trackMask.getSize().x || 
		position.y >= trackMask.getSize().y) {
		return false;
	}
	
	sf::Vector2u pixelPos(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y));
	sf::Color pixelColor = trackMask.getPixel(pixelPos);

	return pixelColor.r > 128;
}

float TrackPhysic::getRayDistance(sf::Vector2f startPosition, float angle, float maxDistance) const {
	sf::Vector2f direction(std::cos(angle), std::sin(angle));
	sf::Vector2f currentPos = startPosition;

	float traveledDistance = 0.0f;
	float stepSize = 2.0f; // for accuracy - performance balance

	while (traveledDistance < maxDistance) {
		currentPos.x += direction.x * stepSize;
		currentPos.y += direction.y * stepSize;
		traveledDistance += stepSize;

		int currentX = static_cast<int>(currentPos.x);
		int currentY = static_cast<int>(currentPos.y);

		sf::Vector2u tempVec(currentX, currentY);

		//if it collides with something, return traveled distance
		if (currentX < 0 || currentY < 0 || currentX >= trackMask.getSize().x || currentY >= trackMask.getSize().y ||
			trackMask.getPixel(tempVec) == sf::Color::Black) {
			return traveledDistance;
		}
	}
	
	//if it collides with nothing, return max distance
	return maxDistance;
}