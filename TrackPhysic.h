#pragma once
#include <SFML/Graphics.hpp>

class TrackPhysic {
private:
	sf::Image trackMask;

public:
	TrackPhysic(const std::string& path);
	bool isOnTrack(sf::Vector2f position) const;
	float getRayDistance(sf::Vector2f position, float angle, float maxDistance) const;
};