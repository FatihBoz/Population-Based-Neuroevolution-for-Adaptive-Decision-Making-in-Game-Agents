#include "TrackVisual.h"
#include <iostream>


sf::Texture TrackVisual::loadTexture(const std::string& path) {
	sf::Texture tex;
	if (!tex.loadFromFile(path)) {
		throw std::runtime_error("Failed to load track texture: " + path);
	}
	return tex;
}


//First initialize the texture, then the sprite with the texture
TrackVisual::TrackVisual(const std::string& path)
	: trackTexture(loadTexture(path)), trackSprite(trackTexture)
{
}

void TrackVisual::draw(sf::RenderWindow& window) {
	window.draw(trackSprite);
}