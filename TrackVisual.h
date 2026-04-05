#pragma once
#include<SFML/Graphics.hpp>
#include <string>

class TrackVisual {
private:
    sf::Texture trackTexture;
    sf::Sprite  trackSprite;

    static sf::Texture loadTexture(const std::string& path);

public:
    TrackVisual(const std::string& path);
    void draw(sf::RenderWindow& window);
};